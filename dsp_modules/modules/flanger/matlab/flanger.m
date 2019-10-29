classdef flanger < handle
    % MEMORY
    properties
        input_blocksize; % self explanatory
        max_delay;
        max_delayunits;
        sampling_rate;
        pi_cnt;
        pi_reset;
        sin_term;
        sin_inc;
        output_buffer;
        delay_buffer;
        wr_ptr;    
        time_shift_idx;
        n;
    end
    
    methods
        %% init
        function obj = flanger(input_blocksize, sampling_rate,rate,delay)
            
            obj.input_blocksize = input_blocksize;
            obj.sampling_rate = sampling_rate;
            obj.max_delay = delay;
            obj.max_delayunits = 500;%ceil(0.015*obj.sampling_rate);
            rate = rate;%-> how fast the delay oscilates, gives the rate of the flanger
            obj.sin_inc = (rate/obj.sampling_rate)*2*pi;
            obj.sin_term = 0;
            obj.pi_reset = floor( 1 / (rate / sampling_rate));
            obj.pi_cnt = 0;
            
            obj.delay_buffer = zeros(obj.max_delayunits*2,1);
            obj.output_buffer = zeros(48,1);
            obj.wr_ptr = 1;
        end
        
        %% apply
        function flanger_apply(obj,input_block)
            
            % check if new input block fits in delay_buffer
            space = length(obj.delay_buffer) - (obj.wr_ptr -1 + obj.input_blocksize);
            if space <= 0 % doesnt fit
                % first write the amount that fits
                obj.delay_buffer(obj.wr_ptr:obj.wr_ptr+obj.input_blocksize+space - 1) = input_block(1:obj.input_blocksize+space);
                % then rewind wr pointer and write the rest of the block 
                obj.wr_ptr = 1;
                obj.delay_buffer(obj.wr_ptr:obj.wr_ptr - space -1) = input_block(obj.input_blocksize+space + 1:obj.input_blocksize);
                obj.wr_ptr = obj.wr_ptr - space;
            else
                % if it fits, append it
                obj.delay_buffer(obj.wr_ptr:obj.wr_ptr+obj.input_blocksize-1) = input_block;
                obj.wr_ptr = obj.wr_ptr + obj.input_blocksize;
            end
            
            
            for i = 1:obj.input_blocksize
                
                obj.sin_term = obj.sin_term + obj.sin_inc;
                obj.pi_cnt = obj.pi_cnt + 1;
                if obj.pi_cnt >= obj.pi_reset
                    obj.sin_term = 0;
                    obj.pi_cnt = 0;
                end
                delay_offset = obj.max_delay/2;
                time_delay = delay_offset*sin(obj.sin_term)+delay_offset;
                obj.n = ceil(obj.sampling_rate*time_delay); 
                time_shift_idx = obj.wr_ptr- obj.n + (i-1) - obj.input_blocksize; % idx of delayed sample  with reference to current write pointer
 
                if (time_shift_idx) < 1 % if idx is under lower limit, wrap backwards to end of buffer
                    time_shift_idx = length(obj.delay_buffer) + time_shift_idx;
                end
               if time_shift_idx > length(obj.delay_buffer) % if idx is larger than length of delaybuffer, start fresh from beginning of buffer
                    time_shift_idx = time_shift_idx - length(obj.delay_buffer);
               end
               obj.time_shift_idx = time_shift_idx-1;
                obj.output_buffer(i) = input_block(i) +  obj.delay_buffer(time_shift_idx);
            end
        end
    end
end



