addpath('../matlab');

input = audioread('../../../test-tools/signals/headset_rx_in.wav');

BLOCKSIZE = 64;

% run and write testvector to file
if ~exist('testvectors/matlab','dir')
  mkdir('testvectors/matlab');
end
fo0 = fopen('testvectors/matlab/testvector_x.f32','wb');

o = empty_module_template(BLOCKSIZE);
for i = 1:BLOCKSIZE:length(input)-BLOCKSIZE
    in1 = input(i:i+BLOCKSIZE-1,:);
    o.apply(in1);
    fwrite(fo0, o.output, 'float32');
end
fclose('all');
