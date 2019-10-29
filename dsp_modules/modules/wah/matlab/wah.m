classdef wah < handle
    % MEMORY
    properties
        input_blocksize; % self explanatory
        sampling_rate;
        output_buffer;
        
        freq_low;
        freq_high;
        freq_delta;     % wah frequency, how many Hz are cycled through pr sample
        freq_center;    % pass band center freq
        Q;              % pass band width, lower value means smaller band
        
        yb_old;        
        yl_old;
                
    end
    
    methods
        %% init
        function obj = wah(input_blocksize, sampling_rate,freq_low,freq_high,freq_delta,Q)
            obj.yb_old = 0;
            obj.yl_old = 0;
            obj.input_blocksize = input_blocksize;
            obj.sampling_rate = sampling_rate;
            obj.freq_low = freq_low;
            obj.freq_high = freq_high;
            obj.freq_delta = freq_delta;
            obj.freq_center = obj.freq_low;
            obj.Q = Q;
            
            obj.output_buffer = zeros(input_blocksize,1);
            
        end
        
        %% apply
        function wah_apply(obj,input_block)
            
            for i = 1:obj.input_blocksize
                
                F1 = 2*sin((pi*obj.freq_center)/obj.sampling_rate);
                
                yh = input_block(i) - obj.yl_old - obj.Q*obj.yb_old;
                yb = F1*yh + obj.yb_old;
                yl = F1*yb + obj.yl_old;
                obj.output_buffer(i) = yb;
                obj.yb_old = yb;
                obj.yl_old = yl;
                
                obj.freq_center = obj.freq_center + obj.freq_delta;
                if obj.freq_center > obj.freq_high % top reached! count down now!
                    obj.freq_center = obj.freq_high;
                    obj.freq_delta = obj.freq_delta * -1;
                end
                
                if obj.freq_center < obj.freq_low % bottom reached! count up now!
                    obj.freq_center = obj.freq_low;
                    obj.freq_delta = obj.freq_delta * -1;
                end
                
                
            end
        end
    end
end



