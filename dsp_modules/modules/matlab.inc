export MATLAB_EXEC = $(shell ./../../../test-tools/matlab/locateMatlab.py)
export MATLAB = $(MATLAB_EXEC) -wait -singlecompthread -nosplash -minimize -nodisplay -nojvm -nodesktop
