#include <stdio.h>
#include "../../../test-tools/c/fopnchk/fopnchk.h"
#include <modules.h>

int main() {      
    printf("\n");
    printf("-------------\n");
    printf("-- TESTING --\n");
    printf("-------------\n");  

    float freq_low = 500;
    float freq_high = 1500;
    float freq_delta = 0.05;
    float Q = 0.1;
    
    int sampling_rate = 16000;
    int block_size = 128;

     // READ FILE
    FILE *f_in;
    f_in = fopen("../../../test-tools/signals/cleanguitar_sample.f32","rb");
    if (!f_in) {
        printf("Unable to open input file!");
        return -1;
    }  

    FILE *f_out = fopnchk("testvectors/c/output.f32","wb");

    if (!f_out) {
        printf("Unable to open output file!");
        return -1;
    }  
    
    t_wah_data wah_data;
    int init_code = wah_init(&wah_data, block_size,sampling_rate, freq_low, freq_high, freq_delta, Q);
    if (init_code!=0) printf("Init error code: %i\n", init_code);

    float inbuf[block_size];
    while (fread(inbuf, sizeof(float), block_size, f_in) == block_size)
    {
        wah_apply(&wah_data, inbuf);

        fwrite(&wah_data.output, sizeof(float), block_size, f_out);
    }

    fopnchk_close_all();    
    return 0;
}
