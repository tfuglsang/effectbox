# Test that maltab works on server
#
#
# By cnorup@jabra.com

export MATLAB_EXEC = $(shell ./locateMatlab.py)
export MATLAB = $(MATLAB_EXEC) -wait -singlecompthread -nosplash -minimize -nodisplay -nojvm -nodesktop

testvectors_sub/matlab:
	whoami
	@echo "Testing..."
	@$(MATLAB) -r "try, diary('matlab_test.log'), \
	catch err, \
	disp(['In ' err.stack(1).file]), disp(['ERROR! on line ' num2str(err.stack(1).line) ': ' err.message ]), \
	exit(1); end; exit(0);"
	@cat matlab_test.log
	@echo "Matlab is done!"
	@echo " "
