#include <stdarg.h>
#include <string.h>
#include "save_input.h"

int save_input(const unsigned int _device_address, const char* _dest_filename, ... /* _src_filenames */) {
    va_list src_filenames;
    int addr = _device_address;
    FILE *f_out = fopen(_dest_filename, "w");
    if (f_out) {
        va_start(src_filenames, _dest_filename);
        for(;;) {
            const char * src_filename = va_arg(src_filenames, const char *);
            if (!src_filename) {
                break;
            }
            FILE *f_in = fopen(src_filename, "rb");
            if (!f_in) {
                break;
            }
            fseek(f_in, 0, SEEK_END);
            int fsize = ftell(f_in);
            rewind(f_in);
            // file name
            char *fn1 = strrchr(src_filename, '/');
            if (!fn1) {
                fn1 = strrchr(src_filename, '\\');
                if (!fn1) {
                    fn1 = (char*)src_filename-1;
                }
            }
            fn1 = fn1 + 1;
            int l = strlen(fn1);
            fprintf(f_out,"E INT 0x%08X = 0x%08X", addr, fsize);
            fprintf(f_out,"\nE CHAR 0x%08X = \"%s\"", addr+4, fn1);
            int a = ((l+4)&(-4)) - l;
            for(int i=0; i<a; i++) {
                fprintf(f_out,",0x00");
            }
            addr += l + a + 4;
            // file data
            for(int i=0; i<fsize; i++) {
                int c = fgetc(f_in);
                if (c == EOF) break;
                if ((i&(BYTES_PERLINE-1))==0) {
                    fprintf(f_out,"\nE CHAR  0x%08X = 0x%02X", addr+i, c);
                }
                else {
                    fprintf(f_out,",0x%02X",c);
                }
            }
            addr += fsize;
            fprintf(f_out,"\n");
            fclose(f_in);
        }
        if (addr != _device_address) {
            fprintf(f_out,"\nE INT  0x%08X = 0,0", addr);
            addr += 8;
        }
        fclose(f_out);
    }
    return addr - _device_address;
}
