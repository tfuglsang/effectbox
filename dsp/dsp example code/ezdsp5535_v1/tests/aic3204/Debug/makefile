################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/c5500_4.4.1

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./aic3204_loop_linein.obj" \
"./aic3204_test.obj" \
"./aic3204_tone_headphone.obj" \
"./main.obj" \
"C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/lib/ezdsp5535bsl.lib" \
$(GEN_CMDS__FLAG) \
--library=cslVC5505.lib \
--library=ezdsp5535bsl.lib \
--library=rts55x.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
aic3204.out \

EXE_OUTPUTS__QUOTED += \
"aic3204.out" \

BIN_OUTPUTS += \
aic3204.hex \

BIN_OUTPUTS__QUOTED += \
"aic3204.hex" \


# All Target
all: aic3204.out

dependents:
	-cd C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/lib/Debug && $(MAKE) clean all

# Tool invocations
aic3204.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS) C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/lib/Debug/../ezdsp5535bsl.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: C5500 Linker'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --define=c5535 --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 -z --reread_libs --warn_sections --search_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/lib" --search_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --search_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/lib" --search_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/ccs_v4.0_examples/cslVC5505/Debug" --map_file="aic3204.map" --xml_link_info="aic3204_linkInfo.xml" --rom_model --heap_size=0x400 --stack_size=0x200 --sys_stacksize=0x200 -o "aic3204.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

aic3204.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C5500 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/hex55"  -o "aic3204.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "aic3204_loop_linein.obj" "aic3204_test.obj" "aic3204_tone_headphone.obj" "main.obj" 
	-$(RM) "aic3204_loop_linein.d" "aic3204_test.d" "aic3204_tone_headphone.d" "main.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/lib/Debug/../ezdsp5535bsl.lib:

-include ../makefile.targets

