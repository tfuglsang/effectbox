clear all
BLOCKSIZE = 128;
FS = 16000;

addpath('../matlab');

% run and write testvector to file
if ~exist('testvectors/matlab','dir')
  mkdir('testvectors/matlab');
end
fo0 = fopen('testvectors/matlab/output.f32','wb');


[in, fs0] = audioread('../../../test-tools/signals/cleanguitar_sample.wav');

freq_low = 500;
freq_high = 1500;
freq_delta = 0.05;
Q = 0.1;
o = wah(BLOCKSIZE, FS, freq_low,freq_high,freq_delta,Q);

number_of_blocks = floor(length(in) / BLOCKSIZE);
output = [];

for i = 1:number_of_blocks   
    
    o.wah_apply(in(i*BLOCKSIZE - BLOCKSIZE + 1:i*BLOCKSIZE));
    output = [output; o.output_buffer];
   
end
% output = output./max(output);
% figure; plot(output);
% 
% maxyb = max(abs(output));
% output = output/maxyb;

audiowrite('wah.wav', output,FS)
fwrite(fo0, output, 'float32');
fclose('all');

