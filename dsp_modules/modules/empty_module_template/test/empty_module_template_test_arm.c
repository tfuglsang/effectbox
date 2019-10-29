#if !(defined(__i386) || defined(_M_IX86))
//
// extnpetrov@jabra.com
// platform stm32 module test template program
//
#include <stdio.h>
#include <string.h>
#include <ARMCM4.h>
#include <system_sim.h>
#include "filenames.h"
#include <gn_ref.h>
#include "modules.h"
#include "../c/empty_module_template.h" // remove this line when you have inserted empty_module_template in modules.h
#include <rsrc.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define BLOCKSIZE 64
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// input data
RSRC(indata0, "../../../test-tools/signals/headset_rx_in.f32", ".rodata");
static RES_DATA rd0;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// time counters
int32_t timer_emt_apply = 0;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
    // empty 
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int execute_test(void) {
    dbg_printf("\n");
    dbg_printf("-------------\n");
    dbg_printf("-- TESTING --\n");
    dbg_printf("-------------\n");

    // init RES_DATA
    init_res_data(rd0, indata0);
    float *inbuf;

    // open files for writing
    // do not redirect debug ITM channels 1-8 and channel 31
    const int N_f_out = 1;
    FILE *f_out[N_f_out];

    // Setup output streams
    for(int i = 0; i<N_f_out; i++) {
        f_out[i] = dbg_fopen(i, "w");
        if (!f_out[i]) {
            dbg_printf("Unable to open IO file! (%d)\n", i);
        }
    }

    static t_empty_module_template_data empty_module_template;
    int init_code = empty_module_template_init(&empty_module_template, BLOCKSIZE);
    if (init_code!=0) printf("Init error code: %i\n", init_code);
    int rd0_cnt = 0;
    for (;;) {
        inbuf = (float*)(&rd0.ptr[rd0_cnt]);
        rd0_cnt += BLOCKSIZE*sizeof(float);
        if (rd0_cnt > rd0.size) break;

        TimerBegin(&timer_emt_apply);
        empty_module_template_apply(&empty_module_template, inbuf);
        TimerEnd(&timer_emt_apply);

        dbg_fwrite(&empty_module_template.output, sizeof(float), BLOCKSIZE, f_out[0]);
    }

    // Cleanup pointers
    dbg_fcloseall();
    dbg_printf("Done!\n");
    dbg_printf("timer empty_module_template_apply: %.2f ms\n",(float)timer_emt_apply/100.0f);
    return 0;
}

#endif // i386
