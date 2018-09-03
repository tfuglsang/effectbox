################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
bsl/ezdsp5535.obj: ../bsl/ezdsp5535.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="bsl/ezdsp5535.d_raw" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsl/ezdsp5535_gpio.obj: ../bsl/ezdsp5535_gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="bsl/ezdsp5535_gpio.d_raw" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsl/ezdsp5535_i2c.obj: ../bsl/ezdsp5535_i2c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="bsl/ezdsp5535_i2c.d_raw" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsl/ezdsp5535_i2s.obj: ../bsl/ezdsp5535_i2s.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="bsl/ezdsp5535_i2s.d_raw" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsl/ezdsp5535_lcd.obj: ../bsl/ezdsp5535_lcd.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="bsl/ezdsp5535_lcd.d_raw" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsl/ezdsp5535_led.obj: ../bsl/ezdsp5535_led.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="bsl/ezdsp5535_led.d_raw" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsl/ezdsp5535_sar.obj: ../bsl/ezdsp5535_sar.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="bsl/ezdsp5535_sar.d_raw" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsl/ezdsp5535_sdcard.obj: ../bsl/ezdsp5535_sdcard.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="bsl/ezdsp5535_sdcard.d_raw" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsl/ezdsp5535_spiflash.obj: ../bsl/ezdsp5535_spiflash.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="bsl/ezdsp5535_spiflash.d_raw" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsl/ezdsp5535_uart.obj: ../bsl/ezdsp5535_uart.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="bsl/ezdsp5535_uart.d_raw" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


