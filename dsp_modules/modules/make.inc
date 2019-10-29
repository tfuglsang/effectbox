# This file contains general setup information for the module build system

mkfile_path := $(realpath $(lastword $(MAKEFILE_LIST)))
module_root_dir := $(patsubst %/,%,$(dir $(mkfile_path)))
module_root_dir_win := $(shell cygpath -m $(module_root_dir))
platform_root_dir := $(realpath $(patsubst modules,,$(dir $(module_root_dir))))
platform_root_dir_win = $(shell cygpath -m $(platform_root_dir))
project_root_dir = $(patsubst %/,%,$(dir $(platform_root_dir)))
project_root_dir_win = $(shell cygpath -m $(project_root_dir))

export TESTTOOLSDIR=$(platform_root_dir)/test-tools

#Optional
# output folders
OBJ_X86 := obj/x86

#Mingw version
export MINGW_PATH=/cygdrive/c/MinGW/bin/
export PATH := $(MINGW_PATH):$(PATH)
export CCO3:=mingw32-gcc -std=c99 -march=native -msse3 -mfpmath=sse -O3
export CCO2:=mingw32-gcc -std=c99 -march=native -msse3 -mfpmath=sse -O2
export CC:=$(CCO3)
export AR:=mingw32-gcc-ar.exe
export RANLIB:=mingw32-gcc-ranlib.exe

#Arm
export ARM_DIR := $(project_root_dir)/toolchain/armeabi
ARM_BIN := $(ARM_DIR)/bin
ARM_CC := $(ARM_BIN)/arm-none-eabi-gcc.exe
ARM_AS := $(ARM_BIN)/arm-none-eabi-as.exe
ARM_LINK := $(ARM_BIN)/arm-none-eabi-gcc.exe
ARM_OBJCOPY := $(ARM_BIN)/arm-none-eabi-objcopy.exe
ARM_CC_SIZE := $(ARM_BIN)/arm-none-eabi-size.exe
ARM_AR := $(ARM_DIR)/arm-none-eabi/bin/ar.exe

ARM_INCLUDES := $(shell cygpath -m $(ARM_DIR))/include

ARM_COMMON_FLAGS := -mthumb -mthumb-interwork -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard

ARM_COMMON_ASM_FLAGS := -Wa,--no-warn -x assembler-with-cpp $(ARM_COMMON_FLAGS) -gdwarf-2 --defsym
ARM_ASM_INCLUDES := -I$(ARM_INCLUDES)

ARM_COMMON_CC_FLAGS  := -Wall $(ARM_COMMON_FLAGS) -O3

#ARM_COMMON_CC_FLAGS += -Werror
ARM_COMMON_CC_FLAGS += -mapcs-frame
#ARM_COMMON_CC_FLAGS += -fpack-struct=4
#ARM_COMMON_CC_FLAGS += -fshort-enums
#ARM_COMMON_CC_FLAGS += -fconserve-stack
ARM_COMMON_CC_FLAGS += -fverbose-asm
#ARM_COMMON_CC_FLAGS += -fno-common
#ARM_COMMON_CC_FLAGS += -fno-merge-constants
#ARM_COMMON_CC_FLAGS += -fno-defer-pop
ARM_COMMON_CC_FLAGS += -fno-strict-aliasing
ARM_COMMON_CC_FLAGS += -gdwarf-3
#ARM_COMMON_CC_FLAGS += -Wa,-adhln="./*.lst"

INCLUDES := $(ARM_INCLUDES) $(platform_root_dir_win)/libraries/arm_math/Include ./
DEFINES := __FPU_PRESENT __VFP_FP__
ARM_CC_INCLUDES := $(foreach include, $(INCLUDES), -I$(include))
ARM_CC_DEFINES := $(foreach define, $(DEFINES), -D$(define))

ARM_CC_FLAGS := $(ARM_COMMON_CC_FLAGS) $(ARM_CC_INCLUDES) $(ARM_CC_DEFINES)
ARM_ASM_FLAGS := $(ARM_COMMON_ASM_FLAGS) $(ARM_ASM_INCLUDES) $(ARM_CC_DEFINES)
ARM_LINK_FLAGS := $(ARM_COMMON_FLAGS) -nostartfiles
#ARM_LINK_FLAGS += -T $(LINK_SCRIPT)

export OPTS = -I$(module_root_dir_win) -I$(platform_root_dir_win)/libraries -I$(platform_root_dir_win)/libraries/arm_math/Include -Wall -g
export DEPFLAGS = -MT $@ -MMD -MP -MF $*.Td
export FOPNCHK:= $(platform_root_dir_win)/test-tools/c/fopnchk/fopnchk.o
export ARM_MATH_LIB=$(platform_root_dir_win)/libraries/arm_math/arm_math.a

export COMPARE_TOOL = $(platform_root_dir)/test-tools/metrics/compareTestVectors.py
