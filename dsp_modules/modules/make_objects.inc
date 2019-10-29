define scan_module
SOURCES +=  $(wildcard $(module_root_dir)/$(1)/c/*.c)
-include $(module_root_dir)/$(1)/c/$(1).mak
endef # scan_module
$(foreach module,$(MODULES),$(eval $(call scan_module,$(module))))


SOURCES:=$(shell cygpath -m $(SOURCES))
OBJECTS := $(SOURCES:.c=.o)

DEPS := $(OBJECTS:.o=.d)

USER_DEFINES = $(addprefix -D, $(EXTRA_DEFINES))

default: $(OBJECTS)

# The rule below combines compilation and depency generation
# and is heavily inspired by:
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/#combine
%.o: %.c
%.o: %.c %.d
	$(CC) $(DEPFLAGS) $(OPTS) -o $@ -c $< $(USER_DEFINES)
	@mv -f $*.Td $*.d && touch $@

#ARM_CC_FLAGS += -Wa,-aln="$@.lst"
%.o: %.c
	$(ARM_CC) $(ARM_CC_FLAGS) -I$(module_root_dir_win) -c $< -o $@ -Wa,-aln="$@.lst"

%.d: ;
.PRECIOUS: %.d

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

clean::
	rm -f $(OBJECTS) $(DEPS) 

#debug_make_objects:
#	@echo SOURCES=$(SOURCES)
#	@echo module_root_dir=$(module_root_dir)
