# add other modules that are used by the test here,
# e.g.
# MODULES:=biquad fir sln FilterBank delay_buffer FIR_synthesis

# add additional test cases, beyond the default one
# run specific test case: make test_sub
# e.g.	
# TEST_CASES:=sub

# default INPUTFILE, overide with: make INPUTFILE=my_wavefile
# e.g.	
# INPUTFILE ?= ../../../test-tools/signals/acoustic_shock_protection_test_file_short.wav

# default FOLDER_NAME, overide with: make FOLDER_NAME=my_folder
# e.g.	
# FOLDER_NAME ?= testing_folder

# See make_test.inc for further details.

######################
# Include make system
######################
module_path := $(realpath ./..)
module_name := $(notdir $(module_path))
include ../../make_test.inc
