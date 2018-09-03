################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
audio_processing.obj: ../audio_processing.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/work/effectbox/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/audio_processing/includes" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="audio_processing.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/work/effectbox/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/audio_processing/includes" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

oled_interface.obj: ../oled_interface.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/work/effectbox/c55xx_csl/inc" --include_path="C:/work/effectbox/dsp/audio_processing/includes" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="oled_interface.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


