################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/c5500_4.4.1

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./bsl/ezdsp5535.obj" \
"./bsl/ezdsp5535_gpio.obj" \
"./bsl/ezdsp5535_i2c.obj" \
"./bsl/ezdsp5535_i2s.obj" \
"./bsl/ezdsp5535_lcd.obj" \
"./bsl/ezdsp5535_led.obj" \
"./bsl/ezdsp5535_sar.obj" \
"./bsl/ezdsp5535_sdcard.obj" \
"./bsl/ezdsp5535_spiflash.obj" \
"./bsl/ezdsp5535_uart.obj" \
"../ezdsp5535bsl.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include bsl/subdir_vars.mk
-include subdir_rules.mk
-include bsl/subdir_rules.mk
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
LIB_OUTPUTS += \
../ezdsp5535bsl.lib \

LIB_OUTPUTS__QUOTED += \
"..\ezdsp5535bsl.lib" \


# All Target
all: ../ezdsp5535bsl.lib

# Tool invocations
../ezdsp5535bsl.lib: $(OBJS) $(LIB_SRCS)
ifneq ($(strip $(ORDERED_OBJS)),)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C5500 Archiver'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/ar55" r "../ezdsp5535bsl.lib" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
endif

# Other Targets
clean:
	-$(RM) $(LIB_OUTPUTS__QUOTED)
	-$(RM) "bsl\ezdsp5535.obj" "bsl\ezdsp5535_gpio.obj" "bsl\ezdsp5535_i2c.obj" "bsl\ezdsp5535_i2s.obj" "bsl\ezdsp5535_lcd.obj" "bsl\ezdsp5535_led.obj" "bsl\ezdsp5535_sar.obj" "bsl\ezdsp5535_sdcard.obj" "bsl\ezdsp5535_spiflash.obj" "bsl\ezdsp5535_uart.obj" 
	-$(RM) "bsl\ezdsp5535.d" "bsl\ezdsp5535_gpio.d" "bsl\ezdsp5535_i2c.d" "bsl\ezdsp5535_i2s.d" "bsl\ezdsp5535_lcd.d" "bsl\ezdsp5535_led.d" "bsl\ezdsp5535_sar.d" "bsl\ezdsp5535_sdcard.d" "bsl\ezdsp5535_spiflash.d" "bsl\ezdsp5535_uart.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

