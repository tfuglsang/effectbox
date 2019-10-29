#include <stdio.h>
#include "../../../test-tools/c/fopnchk/fopnchk.h"
#include <modules.h>

int main() {      
    printf("\n");
    printf("-------------\n");
    printf("-- TESTING --\n");
    printf("-------------\n");  

    float rate = 0.9;
    float delay = 0.015;
    int sampling_rate = 16000;

     // READ FILE
    FILE *f_in;
    f_in = fopen("../../../test-tools/signals/cleanguitar_sample.f32","rb");
    if (!f_in) {
        printf("Unable to open input file!");
        return -1;
    }  

    FILE *f_out = fopnchk("testvectors/c/output.f32","wb");
    
    FILE *f_in_out = fopnchk("testvectors/c/in.f32","wb");
    FILE *f_delaybuf = fopnchk("testvectors/c/delaybuffer.f32","wb");
    FILE *f_wr_ptr = fopnchk("testvectors/c/wr_ptr.s32","wb");
    FILE *f_sin_term = fopnchk("testvectors/c/sin_term.f32","wb");
    FILE *f_pi_cnt = fopnchk("testvectors/c/pi_cnt.s32","wb");

    FILE *f_sin_inc = fopnchk("testvectors/c/sin_inc.f32","wb");
    FILE *f_pi_reset = fopnchk("testvectors/c/pi_reset.s32","wb");
    FILE *f_time_shift_idx = fopnchk("testvectors/c/time_shift_idx.s32","wb");
    FILE *f_n = fopnchk("testvectors/c/n.s32","wb");
    

    t_flanger_data flanger_data;
    int init_code = flanger_init(&flanger_data, BLOCKSIZE,sampling_rate, rate, delay);
    if (init_code!=0) printf("Init error code: %i\n", init_code);

    float inbuf[BLOCKSIZE];
    while (fread(inbuf, sizeof(float), BLOCKSIZE, f_in) == BLOCKSIZE)
    {
        flanger_apply(&flanger_data, inbuf);

        fwrite(&flanger_data.output, sizeof(float), BLOCKSIZE, f_out);

        fwrite(inbuf,                       sizeof(float),  BLOCKSIZE,              f_in_out);
        fwrite(&flanger_data.delay_buffer,  sizeof(float),  FLANGER_DELAYLINE_SIZE, f_delaybuf);
        fwrite(&flanger_data.wr_ptr,        sizeof(int),    1,                      f_wr_ptr);
        fwrite(&flanger_data.sin_term,      sizeof(float),  1,                      f_sin_term);
        fwrite(&flanger_data.pi_cnt,        sizeof(int),    1,                      f_pi_cnt);

        fwrite(&flanger_data.pi_reset,        sizeof(int),    1,                      f_pi_reset);
        fwrite(&flanger_data.sin_inc,        sizeof(int),    1,                      f_sin_inc);

fwrite(&flanger_data.time_shift_idx,        sizeof(int),    1,                      f_time_shift_idx);
fwrite(&flanger_data.n,        sizeof(int),    1,                      f_n);

    }

    fopnchk_close_all();    
    return 0;
}
