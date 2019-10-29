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

# optional: skip matlab
#testvectors/matlab:
#	@echo 
#	@echo "Skip matlab"

ifneq ($(KEIL_IDE),)

TESTVECTORS = testvectors/c testvectors/stm32
#TESTVECTORS = testvectors/c testvectors/c_stm32 testvectors/fixed_stm32

STARTUP_SRCS = startup_ARMCM4.c system_ARMCM4.c keildbg_io.c
SSRCS = $(addprefix "../../../libraries/arm_mp4f/", $(STARTUP_SRCS))
OBJECTS_ARM = $(patsubst %.c, $(OBJ_ARM)/%.o, $(STARTUP_SRCS))
OBJECTS_ARM += $(wildcard ../c/$(OBJ_ARM)/*.o)
#OBJECTS_ARM += $(patsubst ../../FilterBank/c/%.c, ../../FilterBank/c/$(OBJ_ARM)/%.o, $(wildcard ../../FilterBank/c/*.c))

ARM_CC_FLAGS += $(TEST_OPT) -I $(shell cygpath -m $(realpath ./../..))
LINK_SCRIPT = ../../../libraries/arm_mp4f/gcc_arm.ld
ARM_LINK_FLAGS += -T $(LINK_SCRIPT)
ARM_LINK_FLAGS += -Xlinker

ARM_LINK_OBJECTS = $(OBJECTS_ARM) $(ARM_MATH_LIB_CORTEXM4LF) $(ARM_GN_UTIL_CORTEXM4LF)

testvectors/c: $(module_name)_test.exe $(INPUTFILE_RAW) $(module_name)_test.elf 
	mkdir -p $(TESTVECTORS)
	./$(module_name)_test.exe $(INPUTFILE_RAW)
	$(KEIL_IDE) -d  $(module_name)_test.uvprojx
	rm -f EventRecorderStub.scvd
	rm -rf Listings

$(module_name)_test.elf: $(MKDIR_ARM) $(OBJECTS_ARM) $(OBJ_ARM)/$(module_name)_test_arm.o
	$(ARM_LINK) $(ARM_LINK_FLAGS) $(OBJ_ARM)/$(module_name)_test_arm.o $(ARM_LINK_OBJECTS) -o $@

$(OBJ_ARM)/%.o: ../../../libraries/arm_mp4f/%.c
	$(ARM_CC) $(ARM_CC_FLAGS) -c $< -o $@

$(OBJ_ARM)/$(module_name)_test_arm.o: $(module_name)_test_arm.c
	$(ARM_CC) $(ARM_CC_FLAGS) -c $(module_name)_test_arm.c -o $@

clean::
	rm -rf obj
endif
