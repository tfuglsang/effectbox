################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

oled_test.obj: ../oled_test.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/tfuglsang/workspace_v8/ezdsp5535_v1/include" --symdebug:dwarf --diag_warning=225 --memory_model=large --ptrdiff_size=16 --silicon_version=5515 --preproc_with_compile --preproc_dependency="oled_test.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


