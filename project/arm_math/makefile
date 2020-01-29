include ../../modules/make.inc

SRCS = $(wildcard Source/*/*.c)
SRCS_PATH = $(patsubst %.c,%,$(dir $(SRCS)))
SRCS_FOLDERS = $(sort $(SRCS_PATH))
OBJECTS_X86 = $(patsubst %.c, $(OBJ_X86)/%.o, $(notdir $(SRCS)))
OBJECTS_ARM = $(patsubst %.c, $(OBJ_ARM)/%.o, $(notdir $(SRCS)))

OBJS_X86 = $(join $(SRCS_PATH),$(OBJECTS_X86))
OBJS_ARM = $(join $(SRCS_PATH),$(OBJECTS_ARM))

default: create_folders $(ARM_MATH_LIB) $(ARM_MATH_LIB_CORTEXM4LF)

$(OBJS_X86): $(SRCS)
	$(CC) -c $(patsubst %.o,%.c,$(subst $(OBJ_X86)/,,$@)) -o $@ -IInclude/ -I ./

$(OBJS_ARM): $(SRCS)
	$(ARM_CC) $(ARM_CC_FLAGS) -c $(patsubst %.o,%.c,$(subst $(OBJ_ARM)/,,$@)) -o $@ -Wa,-aln=$@.lst

$(ARM_MATH_LIB): $(OBJS_X86)
	$(AR) -rs $(ARM_MATH_LIB) $^

$(ARM_MATH_LIB_CORTEXM4LF): $(OBJS_ARM)
	$(ARM_AR) -r $(ARM_MATH_LIB_CORTEXM4LF) $^

clean:
	find . -type f -name "*.exe" -delete
	find . -type f -name "*.o" -delete
	find . -type f -name "*.d" -delete
	find . -type d -name "obj" -type d -exec rm -rf {} +
	rm -f $(ARM_MATH_LIB)
	rm -f $(ARM_MATH_LIB_CORTEXM4LF)

create_folders:
	mkdir -p $(addsuffix $(OBJ_X86),$(SRCS_FOLDERS)) $(addsuffix $(OBJ_ARM),$(SRCS_FOLDERS))

