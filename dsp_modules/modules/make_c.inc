include ../../make.inc

MODULES:=$(module_name)
include ../../make_objects.inc
default: $(OBJECTS_ARM)
