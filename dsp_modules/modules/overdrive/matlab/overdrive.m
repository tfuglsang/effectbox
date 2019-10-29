classdef overdrive < handle
    % MEMORY
    properties
        input_blocksize; % self explanatory
        sampling_rate;
        output_buffer;
        threshold;
    end
    
    methods
        %% init
        function obj = overdrive(input_blocksize, sampling_rate,threshold)
            
            obj.input_blocksize = input_blocksize;
            obj.sampling_rate = sampling_rate;            
            obj.output_buffer = zeros(input_blocksize,1);
            obj.threshold = threshold;
            
        end
        
        %% apply
        function overdrive_apply(obj,input_block)
            
            for i = 1:obj.input_blocksize
                    
                if abs(input_block(i))< obj.threshold
                    obj.output_buffer(i)=2*input_block(i);
                end
                if abs(input_block(i))>=obj.threshold
                    if input_block(i)> 0
                        obj.output_buffer(i)=(3-(2-input_block(i)*3).^2)/3;
                    end
                    if input_block(i)< 0
                        obj.output_buffer(i) =-(3-(2-abs(input_block(i))*3).^2)/3;
                    end
                end
                if abs(input_block(i))>2*obj.threshold
                    if input_block(i)> 0
                        obj.output_buffer(i) =1;
                    end
                    if input_block(i)< 0
                        obj.output_buffer(i) =-1;
                    end
                end
            end
        end
    end
end



