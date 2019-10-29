###############################################################
# Makefile for running test cases on modules.
# This file is intendended to be included by each module's
# individual makefile
#
# The module makefile must as a ,minimum contain:
#    module_path := $(realpath ./..)
#    module_name := $(notdir $(module_path))
#    include ../../make_test.inc
#
# Optional setup can be specified:
#  MODULES - list of other modules used by the test
#  TEST_CASES - list of test cases, beyond the default one
#  INPUTFILE - specify input wave file for test
#  FOLDER_NAME - needed if running the "folder_test", specify
#                subfolder in <module name>/test/
#
# Facilities provided:
#  - automatic make target generation for test cases, 
#    a test case consists of pairs of files: 
#     	<modules name>_<test case>.c/.m
#  - the default target is to run the default test case, which
#    is:
#       <modules name>_test.c/.m	
#  - a target "test_folder", to run all test on all input wavefiles
#    found in a specified folder:
#       FOLDER_NAME
#
#
# EXAMPLE (from acoustic_shock_protection):
# -----------------------------------------
#
## add other modules that are used by the test here,
# MODULES:=biquad fir sln FilterBank delay_buffer FIR_synthesis
#
## add additional test cases, beyond the default one
## run specific test case: make test_sub
# TEST_CASES:=sub
#
## default INPUTFILE, overide with: make INPUTFILE=my_wavefile
# INPUTFILE ?= ../../../test-tools/signals/acoustic_shock_protection_test_file_short.wav
#
## default FOLDER_NAME, overide with: make FOLDER_NAME=my_folder
# FOLDER_NAME ?= testing_folder
#
# ######################
# # Include make system
# ######################
# module_path := $(realpath ./..)
# module_name := $(notdir $(module_path))
# include ../../make_test.inc
#
# -----------------------------------------
# Author: Bo Vincentz Bonnichsen, June 2018
#
###############################################################

include ../../make.inc
include ../../matlab.inc

MODULES:=$(module_name) $(MODULES)

TEST_CASES:= default $(TEST_CASES)


TEMP_INC:= $(addsuffix /c, $(addprefix -I$(module_root_dir_win)/, $(MODULES)))
INC = $(TEMP_INC) -I$(platform_root_dir_win)/libraries/gn_util -I$(platform_root_dir_win)/test-tools/sniffer -I$(platform_root_dir_win)/test-tools/c/fopnchk

.PHONY: default
default: validate_testvectors

include ../../make_objects.inc

# remove "feature_handler.o" from object list, only the glue should be part of the test
TEMP_OBJ:= $(filter-out $(module_root_dir_win)/feature_handler/c/feature_handler.o, $(OBJECTS))
OBJECTS=$(TEMP_OBJ)
ifneq ($(KEIL_IDE),)
TEST_OPT += -DPREPARE_KEIL_DBGINPUT
endif

ifeq ($(strip $(INPUTFILE)),)
INPUTFILE_MATLAB=
INPUTFILE_RAW=
INPUTFILE_CYG=
INPUTFILE_RAW_CYG=
else
INPUTFILE_MATLAB=$(shell cygpath -w $(INPUTFILE))
INPUTFILE_RAW=$(INPUTFILE:.wav=.f32)
INPUTFILE_CYG= $(shell cygpath $(INPUTFILE))
INPUTFILE_RAW_CYG= $(shell cygpath $(INPUTFILE_RAW))
endif

# Helper target - build .f32 testvector if this is missing.
$(INPUTFILE_RAW):
	@echo "Create binary .f32 file from wav:"
	sox $(INPUTFILE_CYG) -r 16000 $(INPUTFILE_RAW_CYG)
	@echo " "

define run_test_case
ifeq (default,$(1))
TC_$(1):=
else
TC_$(1):=_$(1)
endif

.PHONY: test$$(TC_$(1))
test$$(TC_$(1)): validate_testvectors$$(TC_$(1))

.PHONY: header$$(TC_$(1))
header$$(TC_$(1)):
	@echo "----------------------------------------------------------"
	@echo " Test case: $(module_name)_test$$(TC_$(1)), Input file: $(INPUTFILE)"
	@echo "----------------------------------------------------------"

MATLAB_RUN_COMMAND$$(TC_$(1)) := 	"try diary('matlab_test$$(TC_$(1)).log'),\
						 input_file='$(INPUTFILE_MATLAB)'; \
						 run('$(module_name)_test$$(TC_$(1)).m');\
						 catch err,\
						 disp(['In ' err.stack(1).file]),\
						 disp(['ERROR! on line ' num2str(err.stack(1).line) ': ' err.message ]),\
						 exit(1); end; exit(0);"

# Matlab testvectors will be built if they are missing
# TODO: check how to do this: .DELETE_ON_ERROR: testvectors/matlab
testvectors$$(TC_$(1))/matlab: $(module_name)_test$$(TC_$(1)).m
	@echo "Generating Matlab testvectors... : testvectors$$(TC_$(1))/matlab"
	@mkdir -p testvectors$$(TC_$(1))/matlab
	@$(MATLAB) -r $$(MATLAB_RUN_COMMAND$$(TC_$(1)))
	@echo "Matlab is done!"
	@echo " "

# Force build testvectors everytime
.PHONY: testvectors$$(TC_$(1))/c
testvectors$$(TC_$(1))/c: testvectors$$(TC_$(1))/matlab $(module_name)_test$$(TC_$(1)).exe $(INPUTFILE_RAW)
	mkdir -p testvectors$$(TC_$(1))/c
	./$(module_name)_test$$(TC_$(1)).exe $(INPUTFILE_RAW)

$(module_name)_test$$(TC_$(1)).exe: $(module_name)_test$$(TC_$(1)).c $(OBJECTS)
		$(CC) $(OPTS) $(TEST_OPT) -o $$@ $$^ $(INC) $(LD_LIBS) $(LD_GN_UTIL) $(ARM_MATH_LIB) $(FOPNCHK)


validate_testvectors$$(TC_$(1)): header$$(TC_$(1)) testvectors$$(TC_$(1))/c
	$(COMPARE_TOOL) testvectors$$(TC_$(1))/

matlab$$(TC_$(1)):
	$(MATLAB) -r "$(module_name)$(TC_$(1))_test; exit"

clean$$(TC_$(1)):: 
	rm -rf testvectors$$(TC_$(1))

endef #run_test_case
$(foreach test_case,$(TEST_CASES),$(eval $(call run_test_case,$(test_case))))

clean:: clean_test_folder 
	rm -f *.exe *.elf *.dll *.log *.map
	rm -rf testvectors_*


###############################################################
# Functionality for running tests on all wav files in a folder
# Usage:
# make test_folder FOLDER_NAME=<name of folder>	OUT_SUB_FOLDER=<name_of_subfolder_with_parameter_set_1>
# # if you change some parameter and want to compare the outputs
# make test_folder FOLDER_NAME=<name of folder>	OUT_SUB_FOLDER=<name_of_subfolder_with_parameter_set_2>
# make test_folder_compare
###############################################################
IN_WAVS = $(wildcard ./$(FOLDER_NAME)/*_in.wav)
IN_FILES = $(subst ./$(FOLDER_NAME)/, , $(IN_WAVS))
IN_FILENAME = $(IN_FILES:in.wav=)
IN_16K_WAVS = $(subst in.wav,in_16k.wav, $(IN_WAVS))
IN_RAW = $(IN_WAVS:.wav=.f32)
OUT_FILES = $(subst _in.f32,_out.f32, $(subst ./$(FOLDER_NAME)/,./out/testvectors/$(OUT_SUB_FOLDER)/, $(IN_RAW)))
OUT_WAV_FILES = $(subst /testvectors/$(OUT_SUB_FOLDER),/$(OUT_SUB_FOLDER), $(subst .f32,.wav, $(OUT_FILES)))
%_in_16k.wav: %_in.wav
	sox $< -r 16000 $@

%.f32: %.wav
	sox $< -r 16000 $@

./out/testvectors/$(OUT_SUB_FOLDER)/%_out.f32: ./$(FOLDER_NAME)/%_in.f32 $(module_name)_test.exe $(IN_16K_WAVS) $(IN_RAW)
	@mkdir -p testvectors/c
	@mkdir -p out/testvectors/$(OUT_SUB_FOLDER)
	@mkdir -p out/$(OUT_SUB_FOLDER)
	@echo "---------" 
	@echo "New File!" 
	@echo "---------"
	./$(module_name)_test.exe $< $@

./out/$(OUT_SUB_FOLDER)/%_out.wav: ./out/testvectors/$(OUT_SUB_FOLDER)/%_out.f32
	@echo "Converting to wav: "
	sox -r 16000 -c 1 $< $@
	@echo "Done!"  
	@echo " "

.SECONDARY: $(IN_16K_WAVS) $(IN_RAW) $(OUT_FILES)

.PHONY test_folder:
test_folder: $(OUT_WAV_FILES)

.PHONY test_folder_compare:
test_folder_compare: 
	$(COMPARE_TOOL) out/testvectors/

clean_test_folder:
	rm -f $(IN_16K_WAVS) $(IN_RAW)
	rm -rf out




debug_make_test:
	@echo project_root_dir=$(project_root_dir)
	@echo ARM_CC = $(ARM_CC)
	@echo ARM_LINK = $(ARM_LINK)
	@echo ARM_MATH_LIB_CORTEXM4LF=$(ARM_MATH_LIB_CORTEXM4LF)
	@echo platform_root_dir=$(platform_root_dir)
	@echo module_root_dir=$(module_root_dir)
	@echo OBJECTS=$(OBJECTS)
	@echo MODULES=$(MODULES)
	@echo INC=$(INC)
	@echo MAKEFILE_LIST=$(MAKEFILE_LIST)
	@echo TEST_OPT = $(TEST_OPT)
