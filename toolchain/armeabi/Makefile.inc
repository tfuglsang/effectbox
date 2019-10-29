#-*-makefile-*-
####################################################################################################
# ARM EABI makefile for solaris platform
#
# Homepage: https://launchpad.net/gcc-arm-embedded
# Currently supports version 4.9.3 2014q4
# 
# Author: Christian Paulsen (cpaulsen@jabra.com)
#
####################################################################################################

# Toolchain location
ARM_DIR := $(PLATFORM_DIR)/armeabi
ARM_BIN := $(ARM_DIR)/bin

# define debugger files
APPL_ELF := $(TARGET_DIR)/$(PRODUCT_NAME).elf
ifneq (,$(UBOOT_HEX))
UBOOT_ELF := $(UBOOT_HEX:.hex=.elf)
else
# todo - must generate name
UBOOT_ELF := $(UBOOT_TARGET_DIR)/$(PRODUCT_NAME)_u_boot.elf
endif
ifneq (,$(UPDATER_HEX))
UPDATER_ELF := $(UPDATER_HEX:.hex=.elf)
else
# todo - must generate name
UPDATER_ELF := $(UPDATER_TARGET_DIR)/$(PRODUCT_NAME)_updater.elf
endif

# Compiler
ARM_CC 				:= PATH=$(ARM_BIN) arm-none-eabi-gcc
ARM_AS 				:= PATH=$(ARM_BIN) arm-none-eabi-as
ARM_LINK 			:= PATH=$(ARM_BIN) arm-none-eabi-gcc
ARM_OBJCOPY 		:= PATH=$(ARM_BIN) arm-none-eabi-objcopy
CC_SIZE 			:= PATH=$(ARM_BIN) arm-none-eabi-size
CPP := cpp

ARM_INCLUDES := $(ARM_DIR)/include
INCLUDES += $(ARM_INCLUDES)
UBOOT_INCLUDES += $(ARM_INCLUDES)
UPDATER_INCLUDES += $(ARM_INCLUDES)

ARM_CC_INCLUDES := $(foreach include, $(INCLUDES), -I$(include))
ARM_CC_DEFINES := $(foreach define, $(DEFINES), -D$(define))
UBOOT_ARM_CC_INCLUDES := $(foreach include, $(UBOOT_INCLUDES), -I$(include))
UBOOT_ARM_CC_DEFINES := $(foreach define, $(UBOOT_DEFINES), -D$(define))
UPDATER_ARM_CC_INCLUDES := $(foreach include, $(UPDATER_INCLUDES), -I$(include))
UPDATER_ARM_CC_DEFINES := $(foreach define, $(UPDATER_DEFINES), -D$(define))

ARM_CPU ?= cortex-m3

ARM_COMMON_FLAGS := -c -mthumb -mcpu=$(ARM_CPU) -Wno-attributes -g

ARM_COMMON_ASM_FLAGS := -Wa,--no-warn -x assembler-with-cpp $(ARM_COMMON_FLAGS)
ARM_COMMON_ASM_FLAGS += $(EXTRA_ASM_FLAGS)

ARM_COMMON_CC_FLAGS  := -std=c99 -Wall -Werror -fno-builtin -ffunction-sections -fdata-sections $(ARM_COMMON_FLAGS) -Os

ARM_COMMON_CC_FLAGS += -fpack-struct=4
ARM_COMMON_CC_FLAGS += -fshort-enums
ARM_COMMON_CC_FLAGS += -ffunction-sections
ARM_COMMON_CC_FLAGS += -fdata-sections
ARM_COMMON_CC_FLAGS += -fconserve-stack
ARM_COMMON_CC_FLAGS += -fverbose-asm
ARM_COMMON_CC_FLAGS += -fno-common
ARM_COMMON_CC_FLAGS += -fno-merge-constants
ARM_COMMON_CC_FLAGS += -fno-defer-pop
ARM_COMMON_CC_FLAGS += -fno-strict-aliasing
ARM_COMMON_CC_FLAGS += -gdwarf-3
ARM_COMMON_CC_FLAGS += -fmax-errors=10

ARM_COMMON_CC_FLAGS += $(EXTRA_CC_FLAGS)

ARM_CC_FLAGS :=  $(ARM_COMMON_CC_FLAGS) $(ARM_CC_INCLUDES) $(ARM_CC_DEFINES)
ARM_ASM_FLAGS := $(ARM_COMMON_ASM_FLAGS) $(ARM_CC_DEFINES)
UBOOT_ARM_CC_FLAGS := $(ARM_COMMON_CC_FLAGS) $(UBOOT_ARM_CC_INCLUDES) $(UBOOT_ARM_CC_DEFINES)
UPDATER_ARM_CC_FLAGS := $(ARM_COMMON_CC_FLAGS) $(UPDATER_ARM_CC_INCLUDES) $(UPDATER_ARM_CC_DEFINES)

ARM_COMMON_LINK_FLAGS := -Wl,--fatal-warnings
ARM_COMMON_LINK_FLAGS += -Wl,--gc-sections
ARM_COMMON_LINK_FLAGS += -Wl,-static 
ARM_COMMON_LINK_FLAGS += -Wl,-nostdlib
ARM_COMMON_LINK_FLAGS += -mcpu=$(ARM_CPU)
ARM_COMMON_LINK_FLAGS += -mthumb 
ARM_COMMON_LINK_FLAGS += -specs=nano.specs
ARM_COMMON_LINK_FLAGS += $(EXTRA_LINK_FLAGS)
ARM_COMMON_LINK_FLAGS += -L $(ARM_DIR)

ARM_LINK_FLAGS := $(ARM_COMMON_LINK_FLAGS) -T $(LINK_SCRIPT)
ARM_LINK_LIBS :=

UBOOT_ARM_LINK_FLAGS := $(ARM_COMMON_LINK_FLAGS) -T $(UBOOT_LINK_SCRIPT)
UBOOT_ARM_LINK_LIBS :=

UPDATER_ARM_LINK_FLAGS := $(ARM_COMMON_LINK_FLAGS) -T $(UPDATER_LINK_SCRIPT)
UPDATER_ARM_LINK_LIBS :=

# Object files
ARM_OBJS := $(patsubst $(EXT_PLATFORM_DIR)/%,$(TARGET_DIR)/platform_ext/%,$(patsubst $(PLATFORM_DIR)/%,$(TARGET_DIR)/%,$(SOURCES:.c=.o)))\
            $(patsubst $(EXT_PLATFORM_DIR)/%,$(TARGET_DIR)/platform_ext/%,$(patsubst $(PLATFORM_DIR)/%,$(TARGET_DIR)/%,$(ASM_SOURCES:.s=.o)))\
            $(patsubst $(GN_DSP_PLATFORM_DIR)/%,$(TARGET_DIR)/platform_dsp/%,$(patsubst $(PLATFORM_DIR)/%,$(TARGET_DIR)/%,$(EXT_DSP_SOURCES:.c=.o)))\
            $(patsubst $(PROJECT_DIR)/%,$(TARGET_DIR)/%,$(PROJECT_SOURCES:.c=.o))\
            $(patsubst $(PROJECT_DIR)/%,$(TARGET_DIR)/%,$(ASM_PROJECT_SOURCES:.s=.o))

# Update depend list
ARM_CC_DEPENDS := $(patsubst $(EXT_PLATFORM_DIR)/%,$(TARGET_DIR)/platform_ext/%,$(patsubst $(PLATFORM_DIR)/%,$(TARGET_DIR)/%,$(SOURCES:.c=.d)))
ARM_CC_DEPENDS += $(patsubst $(GN_DSP_PLATFORM_DIR)/%,$(TARGET_DIR)/platform_dsp/%,$(patsubst $(PLATFORM_DIR)/%,$(TARGET_DIR)/%,$(EXT_DSP_SOURCES:.c=.d)))
ARM_CC_DEPENDS += $(patsubst $(PROJECT_DIR)/%,$(TARGET_DIR)/%,$(PROJECT_SOURCES:.c=.d))

ifneq (,$(UBOOT_TARGET_DIR))
# Object files for boot loader
UBOOT_ARM_OBJS := $(patsubst $(EXT_PLATFORM_DIR)/%,$(UBOOT_TARGET_DIR)/platform_ext/%,$(patsubst $(PLATFORM_DIR)/%,$(UBOOT_TARGET_DIR)/%,$(UBOOT_SOURCES:.c=.o)))\
                  $(patsubst $(EXT_PLATFORM_DIR)/%,$(UBOOT_TARGET_DIR)/platform_ext/%,$(patsubst $(PLATFORM_DIR)/%,$(UBOOT_TARGET_DIR)/%,$(UBOOT_ASM_SOURCES:.s=.o)))\
                  $(patsubst $(PROJECT_DIR)/%,$(UBOOT_TARGET_DIR)/%,$(UBOOT_PROJECT_SOURCES:.c=.o))\
                  $(patsubst $(PROJECT_DIR)/%,$(UBOOT_TARGET_DIR)/%,$(UBOOT_ASM_PROJECT_SOURCES:.s=.o))
# Update depend list
ARM_CC_DEPENDS += $(patsubst $(EXT_PLATFORM_DIR)/%,$(UBOOT_TARGET_DIR)/platform_ext/%,$(patsubst $(PLATFORM_DIR)/%,$(UBOOT_TARGET_DIR)/%,$(UBOOT_SOURCES:.c=.d)))
ARM_CC_DEPENDS += $(patsubst $(PROJECT_DIR)/%,$(UBOOT_TARGET_DIR)/%,$(UBOOT_PROJECT_SOURCES:.c=.d))
endif

ifneq (,$(UPDATER_TARGET_DIR))
# Object files for updater
UPDATER_ARM_OBJS := $(patsubst $(EXT_PLATFORM_DIR)/%,$(UPDATER_TARGET_DIR)/platform_ext/%,$(patsubst $(PLATFORM_DIR)/%,$(UPDATER_TARGET_DIR)/%,$(UPDATER_SOURCES:.c=.o)))\
                  $(patsubst $(EXT_PLATFORM_DIR)/%,$(UPDATER_TARGET_DIR)/platform_ext/%,$(patsubst $(PLATFORM_DIR)/%,$(UPDATER_TARGET_DIR)/%,$(UPDATER_ASM_SOURCES:.s=.o)))\
                  $(patsubst $(PROJECT_DIR)/%,$(UPDATER_TARGET_DIR)/%,$(UPDATER_PROJECT_SOURCES:.c=.o))\
                  $(patsubst $(PROJECT_DIR)/%,$(UPDATER_TARGET_DIR)/%,$(UPDATER_ASM_PROJECT_SOURCES:.s=.o))

# Update depend list
ARM_CC_DEPENDS += $(patsubst $(EXT_PLATFORM_DIR)/%,$(UPDATER_TARGET_DIR)/platform_ext/%,$(patsubst $(PLATFORM_DIR)/%,$(UPDATER_TARGET_DIR)/%,$(UPDATER_SOURCES:.c=.d)))
ARM_CC_DEPENDS += $(patsubst $(PROJECT_DIR)/%,$(UPDATER_TARGET_DIR)/%,$(UPDATER_PROJECT_SOURCES:.c=.d))
endif

CC_DEPENDS += $(ARM_CC_DEPENDS)

# Preprocess the loader files
$(TARGET_DIR)/%.ld: $(PROJECT_DIR)/%.ld
	-@mkdir --parents $(dir $@)
ifeq (y,$(FEATURE_SIGNATURE))
	$(CPP) -P -DFLASH_SIZE=$(FLASH_SIZE) -DFEATURE_SIGNATURE $< $@ 
else
	$(CPP) -P -DFLASH_SIZE=$(FLASH_SIZE) $< $@ 
endif

define DEPEND_HACK
	@sed -i -e 's/\r//' -e's/\\\(.\)/\/\1/g' $(@:.o=.d) ;\
    cp $(@:.o=.d) $(patsubst %.d,%.Td,$(@:.o=.Td)) ;\
    sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $(patsubst %.d,%.Td,$(@:.o=.Td)) >> $(@:.o=.d)
endef		
# Compile rules
define ASM_COMPILE
	-@mkdir --parents $(dir $@)
	@echo Generating DEP/OBJ for $< ; \
	$(ARM_CC) $(ARM_ASM_FLAGS) -o $(@:.d=.o) $<
endef
define COMPILE
	-@mkdir --parents $(dir $@)
	@echo Generating DEP/OBJ for $< ; \
	$(ARM_CC) $(ARM_CC_FLAGS) -MMD -o $(@:.d=.o) $<
	$(DEPEND_HACK)
endef
define LOADER_COMPILE
	-@mkdir --parents $(dir $@)
	@echo Generating loader DEP/OBJ for $< ; \
	$(ARM_CC) $(UBOOT_ARM_CC_FLAGS) -MMD -o $(@:.d=.o) $<
	$(DEPEND_HACK)
endef
define UPDATER_COMPILE
	-@mkdir --parents $(dir $@)
	@echo Generating updater DEP/OBJ for $< ; \
	$(ARM_CC) $(UPDATER_ARM_CC_FLAGS) -MMD -o $(@:.d=.o) $<
	$(DEPEND_HACK)
endef

$(UBOOT_TARGET_DIR)/%.d: $(PLATFORM_DIR)/%.c
	$(LOADER_COMPILE)

$(UBOOT_TARGET_DIR)/%.o: $(PLATFORM_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(LOADER_COMPILE)

$(UBOOT_TARGET_DIR)/platform_ext/%.d: $(EXT_PLATFORM_DIR)/%.c
	$(LOADER_COMPILE)

$(UBOOT_TARGET_DIR)/platform_ext/%.o: $(EXT_PLATFORM_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(LOADER_COMPILE)

$(UBOOT_TARGET_DIR)/platform_ext/%.o: $(EXT_PLATFORM_DIR)/%.s $(TARGET_DIR)/cc_depends
	$(ASM_COMPILE)

$(UBOOT_TARGET_DIR)/%.o: $(PLATFORM_DIR)/%.s  $(TARGET_DIR)/cc_depends
	$(ASM_COMPILE)

$(UBOOT_TARGET_DIR)/%.d: $(PROJECT_DIR)/%.c
	$(LOADER_COMPILE)

$(UBOOT_TARGET_DIR)/%.o: $(PROJECT_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(LOADER_COMPILE)


$(UPDATER_TARGET_DIR)/%.d: $(PLATFORM_DIR)/%.c
	$(UPDATER_COMPILE)

$(UPDATER_TARGET_DIR)/%.o: $(PLATFORM_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(UPDATER_COMPILE)

$(UPDATER_TARGET_DIR)/platform_ext/%.d: $(EXT_PLATFORM_DIR)/%.c
	$(UPDATER_COMPILE)

$(UPDATER_TARGET_DIR)/platform_ext/%.o: $(EXT_PLATFORM_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(UPDATER_COMPILE)

$(UPDATER_TARGET_DIR)/%.d: $(PROJECT_DIR)/%.c
	$(UPDATER_COMPILE)

$(UPDATER_TARGET_DIR)/%.o: $(PROJECT_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(UPDATER_COMPILE)

$(UPDATER_TARGET_DIR)/platform_ext/%.o: $(EXT_PLATFORM_DIR)/%.s $(TARGET_DIR)/cc_depends
	$(ASM_COMPILE)

$(UPDATER_TARGET_DIR)/%.o: $(PLATFORM_DIR)/%.s  $(TARGET_DIR)/cc_depends
	$(ASM_COMPILE)


$(TARGET_DIR)/%.o: $(PLATFORM_DIR)/%.s  $(TARGET_DIR)/cc_depends
	$(ASM_COMPILE)

$(TARGET_DIR)/%.d: $(PLATFORM_DIR)/%.c
	$(COMPILE)

$(TARGET_DIR)/%.o: $(PLATFORM_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(COMPILE)

$(TARGET_DIR)/%.d: $(TARGET_DIR)/%.c
	$(COMPILE)

$(TARGET_DIR)/%.d: $(PROJECT_DIR)/%.c
	$(COMPILE)

$(TARGET_DIR)/%.o: $(PROJECT_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(COMPILE)

$(TARGET_DIR)/%.o: $(TARGET_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(COMPILE)

$(TARGET_DIR)/platform_ext/%.o: $(EXT_PLATFORM_DIR)/%.s $(TARGET_DIR)/cc_depends
	$(ASM_COMPILE)

$(TARGET_DIR)/platform_ext/%.d: $(EXT_PLATFORM_DIR)/%.c
	$(COMPILE)

$(TARGET_DIR)/platform_ext/%.o: $(EXT_PLATFORM_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(COMPILE)

$(TARGET_DIR)/platform_dsp/%.d: $(GN_DSP_PLATFORM_DIR)/%.c
	$(COMPILE)

$(TARGET_DIR)/platform_dsp/%.o: $(GN_DSP_PLATFORM_DIR)/%.c $(TARGET_DIR)/cc_depends
	$(COMPILE)

BUILDINFO_OBJ:=$(patsubst $(EXT_PLATFORM_DIR)/%, $(TARGET_DIR)/%, $(patsubst $(PROJECT_DIR)/%, $(TARGET_DIR)/%, $(patsubst $(PLATFORM_DIR)/%, $(TARGET_DIR)/%, $(BUILDINFO:.c=.o))))
UBOOT_BUILDINFO_OBJ:=$(patsubst $(EXT_PLATFORM_DIR)/%, $(UBOOT_TARGET_DIR)/%, $(patsubst $(PROJECT_DIR)/%, $(UBOOT_TARGET_DIR)/%, $(patsubst $(PLATFORM_DIR)/%, $(UBOOT_TARGET_DIR)/%, $(BUILDINFOLDR:.c=.o))))
UPDATER_BUILDINFO_OBJ:=$(patsubst $(EXT_PLATFORM_DIR)/%, $(UPDATER_TARGET_DIR)/%, $(patsubst $(PROJECT_DIR)/%, $(UPDATER_TARGET_DIR)/%, $(patsubst $(PLATFORM_DIR)/%, $(UPDATER_TARGET_DIR)/%, $(BUILDINFO:.c=.o))))

$(APPL_ELF): $(ARM_OBJS) $(ARM_LIBS) $(LINK_SCRIPT) $(BUILDINFO)
	-@mkdir --parents $(dir $@)
ifneq (,$(BUILDINFO))
	$(call GEN_TIMESTAMP, $(TIMESTAMP_HEADER))
	-@mkdir --parents $(dir $(BUILDINFO_OBJ))
	@echo Generating OBJ for $(BUILDINFO) ; \
	$(ARM_CC) $(ARM_CC_FLAGS) -o $(BUILDINFO_OBJ) $(BUILDINFO)
endif
	@echo $(ARM_OBJS) >$(TARGET_DIR)/elf-files.inc
	$(ARM_LINK) $(ARM_LINK_FLAGS) @$(TARGET_DIR)/elf-files.inc $(BUILDINFO_OBJ) $(ARM_LINK_LIBS) -o $@ -Wl,--cref -Wl,-Map=$(@:.elf=.map)

$(APPL_BIN): $(APPL_ELF)
	-@mkdir --parents $(dir $@)
	$(ARM_OBJCOPY) --gap-fill 0xff --output-target=binary $< $(@:.bin=.tmp)
ifeq (y,$(FEATURE_SIGNATURE))
	$(MKSIGNATURE) $(@:.bin=.tmp) $(PRODUCT_NAME)
	cat $(@:.bin=.tmp) $(@:.bin=.sgn) >$@
else
	mv $(@:.bin=.tmp) $@
endif

ifneq (,$(SECOND_SRC_BIN))
.PHONY: $(SECOND_SRC_BIN)
endif
$(SECOND_SRC_BIN):
	@echo Making $@
	@$(MAKE) -j8 -C $(SECOND_BUILD_DIR)

SECOND_SRC_TMP = $(TARGET_DIR)/$(notdir $(SECOND_SRC_BIN:.bin=.tmp))
$(SECOND_TARGET_HEX): $(SECOND_SRC_BIN)
	@echo Making $@
	@cp $< $(SECOND_SRC_TMP:.tmp=.bin)
ifeq (y,$(FEATURE_SIGNATURE))
	@mv $(SECOND_SRC_TMP:.tmp=.bin) $(SECOND_SRC_TMP)
	$(MKSIGNATURE) $(SECOND_SRC_TMP) $(PRODUCT_NAME)
	cat $(SECOND_SRC_TMP) $(SECOND_SRC_TMP:.tmp=.sgn) > $(SECOND_SRC_TMP:.tmp=.bin)
endif		
	$(ARM_OBJCOPY) --gap-fill 0xff --change-addresses $(SECOND_HEX_ADDR) --input-target=binary --output-target=ihex $(SECOND_SRC_TMP:.tmp=.bin) $@

$(APPL_HEX): $(APPL_BIN) $(AUDIO_NVS_FILE)
	-@mkdir --parents $(dir $@)
	@echo Making $@
	$(ARM_OBJCOPY) --gap-fill 0xff --change-addresses $(APPL_IMAGE_ADDR) --input-target=binary --output-target=ihex $< $@
ifdef AUDIO_NVS_FILE
	@cat $@ $(AUDIO_NVS_FILE) | grep -v "^:00000001FF" > $@.tmp
	@echo ":00000001FF" >> $@.tmp
	@mv $@.tmp $@
endif

$(UBOOT_ELF): $(UBOOT_ARM_OBJS) $(UBOOT_ARM_LIBS) $(UBOOT_LINK_SCRIPT)
	-@mkdir --parents $(dir $@)
ifneq (,$(BUILDINFOLDR))
	$(call GEN_TIMESTAMP,  $(TARGET_DIR)/include/loader/timestamp.h)
	-@mkdir --parents $(dir $(UBOOT_BUILDINFO_OBJ))
	@echo Generating loader OBJ for $(BUILDINFOLDR) ; \
	$(ARM_CC) -I $(TARGET_DIR)/include/loader $(UBOOT_ARM_CC_FLAGS) -o $(UBOOT_BUILDINFO_OBJ) $(BUILDINFOLDR)
endif
	@echo $(UBOOT_ARM_OBJS) >$(TARGET_DIR)/loader-elf-files.inc
	$(ARM_LINK) $(UBOOT_ARM_LINK_FLAGS) @$(TARGET_DIR)/loader-elf-files.inc $(UBOOT_BUILDINFO_OBJ) $(UBOOT_ARM_LINK_LIBS) -o $@ -Wl,--cref -Wl,-Map=$(@:.elf=.map)

$(UBOOT_BIN): $(UBOOT_ELF)
	-@mkdir --parents $(dir $@)
	$(ARM_OBJCOPY) --gap-fill 0xff --output-target=binary $< $@

$(UBOOT_HEX): $(UBOOT_ELF)
	-@mkdir --parents $(dir $@)
	$(ARM_OBJCOPY) --gap-fill 0xff --output-target=ihex $< $@


$(UPDATER_ELF): $(UPDATER_ARM_OBJS) $(UPDATER_ARM_LIBS) $(UPDATER_LINK_SCRIPT)
	-@mkdir --parents $(dir $@)
ifneq (,$(BUILDINFO))
	$(call GEN_TIMESTAMP, $(TARGET_DIR)/include/updater/timestamp.h)
	-@mkdir --parents $(dir $(UPDATER_BUILDINFO_OBJ))
	@echo Generating updater OBJ for $(BUILDINFO) ; \
	$(ARM_CC) -I$(TARGET_DIR)/include/updater $(UPDATER_ARM_CC_FLAGS) -o $(UPDATER_BUILDINFO_OBJ) $(BUILDINFO)
endif
	@echo $(UPDATER_ARM_OBJS) >$(TARGET_DIR)/updater-elf-files.inc
	$(ARM_LINK) $(UPDATER_ARM_LINK_FLAGS) @$(TARGET_DIR)/updater-elf-files.inc $(UPDATER_BUILDINFO_OBJ) $(UPDATER_ARM_LINK_LIBS) -o $@ -Wl,--cref -Wl,-Map=$(@:.elf=.map)

$(UPDATER_BIN): $(UPDATER_ELF)
	-@mkdir --parents $(dir $@)
	$(ARM_OBJCOPY) --gap-fill 0xff --output-target=binary $< $@

$(UPDATER_HEX): $(UPDATER_ELF)
	-@mkdir --parents $(dir $@)
	$(ARM_OBJCOPY) --gap-fill 0xff --output-target=ihex $< $@

# Update header list
ARM_HEADERS += $(foreach dir, $(ARM_INCLUDES), $(wildcard $(dir)/*.h))

# add this file to config files
ARMEABI_CONFIG = $(ARM_DIR)/Makefile.inc
CONFIG_GROUPS += ARMEABI_CONFIG

# Include lauterbach target if needed
ifneq (,$(filter lauterbach ulauterbach,$(MAKECMDGOALS)))
 DEBUG_EXT:=elf
 include $(PLATFORM_DIR)/gndebug/lauterbach.mak
endif
ARMEABI_CONFIG += $(PLATFORM_DIR)/gndebug/lauterbach.mak

# Include nexus target if needed
ifneq (,$(filter nexus%,$(MAKECMDGOALS)))
 include $(PLATFORM_DIR)/gndebug/nexus.mak
endif
DIALOG_CONFIG += $(PLATFORM_DIR)/gndebug/nexus.mak
# Add sources to source groups
ARM_SOURCE_GROUPS := 
SOURCE_GROUPS += $(ARM_SOURCE_GROUPS)

# Add headers to the header pool
HEADERS += $(ARM_HEADERS)
HEADER_GROUPS += ARM_HEADERS

# add the hex converter so we can look into hex files
GOALS += $(GN_HEXCONV)

debug_arm:
	@echo ARM_CC = $(ARM_CC)
	@echo
	@echo ARM_LINK = $(ARM_LINK)
	@echo
	@echo ARM_OBJS = $(ARM_OBJS)
	@echo
	@echo ARM_CC_DEPENDS = $(ARM_CC_DEPENDS)
	@echo
	@echo UBOOT_ARM_CC = $(UBOOT_ARM_CC)
	@echo
	@echo UBOOT_ARM_OBJS = $(UBOOT_ARM_OBJS)
	@echo
	@echo UBOOT_ARM_CC_DEPENDS = $(UBOOT_ARM_CC_DEPENDS)
	@echo
	@echo UPDATER_ARM_CC = $(UPDATER_ARM_CC)
	@echo
	@echo UPDATER_ARM_OBJS = $(UPDATER_ARM_OBJS)
	@echo
	@echo UPDATER_ARM_CC_DEPENDS = $(UPDATER_ARM_CC_DEPENDS)
	@echo
	@echo BUILDINFO = $(BUILDINFO_OBJ)
	@echo
	@echo DSP_SRC = $(patsubst $(PLATFORM_DIR)/%,$(TARGET_DIR)/%,$(SOURCES:.c=.o))
	@echo
	@echo PLATFORM_DIR = $(PLATFORM_DIR)
	@echo
	@echo TARGE_DIR = $(TARGET_DIR)
	@echo
	@echo GN_DSP_PLATFORM_DIR =  $(GN_DSP_PLATFORM_DIR)

	
# vim: set ft=make:
