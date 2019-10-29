classdef empty_module_template < handle
    % OUTPUT
    properties
        output;
    end
    % MEMORY
    properties
        N;
    end
    methods
        % INIT
        function obj = empty_module_template(N)
            % init
            obj.N = N;
            obj.reset();
        end
        % RESET
        function reset(obj)
            obj.output = zeros(obj.N,1);
        end
        % APPLY
        function apply(obj, external_input)
            obj.output = external_input;
        end
    end
end
