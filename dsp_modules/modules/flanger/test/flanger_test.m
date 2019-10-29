clear all
BLOCKSIZE = 48;
FS = 16000;

addpath('../matlab');

% run and write testvector to file
if ~exist('testvectors/matlab','dir')
  mkdir('testvectors/matlab');
end
fo0 = fopen('testvectors/matlab/output.f32','wb');

fo_pi_cnt = fopen('testvectors/matlab/pi_cnt.s32','wb');
fo_sin_term = fopen('testvectors/matlab/sin_term.f32','wb');
fo_wr_ptr = fopen('testvectors/matlab/wr_ptr.s32','wb');
fo_delay_buf = fopen('testvectors/matlab/delaybuffer.f32','wb');
fo_in_out = fopen('testvectors/matlab/in.f32','wb');
fo_pi_reset = fopen('testvectors/matlab/pi_reset.s32','wb');
fo_sin_inc = fopen('testvectors/matlab/sin_inc.f32','wb');
fo_time_shift_idx = fopen('testvectors/matlab/time_shift_idx.s32','wb');
fo_n = fopen('testvectors/matlab/n.s32','wb');

[in, fs0] = audioread('../../../test-tools/signals/cleanguitar_sample.wav');
% file_name = 'acoustic.wav';
% file_name = 'cleanguitar_morebass.wav';
% file_name = '.wav';
% [in,fs] = audioread(file_name);

rate = 0.9;
delay = 0.015;
o = flanger(BLOCKSIZE, FS, rate, delay);

number_of_blocks = floor(length(in) / BLOCKSIZE);
output = [];

pi_cnt = [];
sin_term = [];
wr_ptr = [];
delay_buf = [];
in_out = [];
pi_reset = [];
sin_inc = [];
time_shift_idx = [];
n = [];

for i = 1:number_of_blocks   
    
    o.flanger_apply(in(i*BLOCKSIZE - BLOCKSIZE + 1:i*BLOCKSIZE));
    output = [output; o.output_buffer];
    
    pi_cnt = [pi_cnt o.pi_cnt];
    sin_term = [sin_term o.sin_term];
    wr_ptr = [wr_ptr o.wr_ptr-1];
    delay_buf = [delay_buf; o.delay_buffer];
    in_out = [in_out; in(i*BLOCKSIZE - BLOCKSIZE + 1:i*BLOCKSIZE)];
    
    pi_reset = [pi_reset o.pi_reset];
    sin_inc = [sin_inc o.sin_inc];
    time_shift_idx = [time_shift_idx o.time_shift_idx];
    n = [n o.n];
end
% output = output./max(output);
% figure; plot(output);
% audiowrite('flanger.wav', output,fs)
fwrite(fo0, output, 'float32');

fwrite(fo_pi_cnt, pi_cnt, 'int');
fwrite(fo_sin_term, sin_term, 'float32');
fwrite(fo_wr_ptr, wr_ptr, 'int');
fwrite(fo_delay_buf, delay_buf, 'float32');
fwrite(fo_in_out, in_out, 'float32');
fwrite(fo_pi_reset, pi_reset, 'int');
fwrite(fo_sin_inc, sin_inc, 'float32');
fwrite(fo_time_shift_idx, time_shift_idx, 'int');
fwrite(fo_n, n, 'int');
fclose('all');

