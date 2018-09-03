################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
aic3204_loop_linein.obj: ../aic3204_loop_linein.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="aic3204_loop_linein.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

aic3204_test.obj: ../aic3204_test.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="aic3204_test.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

aic3204_tone_headphone.obj: ../aic3204_tone_headphone.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="aic3204_tone_headphone.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

mem_test.obj: ../mem_test.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="mem_test.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

oled_test.obj: ../oled_test.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="oled_test.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

spiflash_test.obj: ../spiflash_test.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="spiflash_test.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

usb.obj: ../usb.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/dsp example code/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="usb.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


