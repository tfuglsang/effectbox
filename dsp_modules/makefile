# Reference platform makefile
#
#
#

# -- Options for sim/run targets
ifndef AUDIOPROCESS
export AUDIOPROCESS=passthrough
endif

ifndef MONITOR
export MONITOR=default
endif

ifndef IO
export IO
endif

ifndef LUA_STARTUP
export LUA_STARTUP=startup.lua
endif

# -- Compiler path - used if not specied by user as env. var.
export MINGW_PATH=/cygdrive/c/MinGW/bin/

# -- Targets
default: offline-application
Nightly_build: default

.PHONY: offline-application
offline-application: modules audioprocess test-tools

# -- DSP Nightly Build
dsp_nightly: modules test-tools
	rm -rf test-tools/metrics/log_data/
	$(MAKE) -C modules test
	$(MAKE) -C modules test_full
	./test-tools/metrics/verifyDataDumps.py test-tools/metrics/log_data/

.PHONY: modules
modules: libraries
	$(MAKE) -C modules

.PHONY: audioprocess
audioprocess:
	$(MAKE) -C audioprocess clean
	$(MAKE) -C audioprocess

.PHONY: test-tools
test-tools:
	$(MAKE) -C test-tools

# Test all modules and look at output logs afterwards
.PHONY: test_modules
test_modules: modules test-tools
	$(MAKE) -C modules test
	./test-tools/metrics/verifyDataDumps.py test-tools/metrics/log_data/

.PHONY: libraries
libraries: 
	$(MAKE) -C libraries

# -- Cleanup!
.PHONY: clean
clean:
	$(MAKE) -C modules clean
	$(MAKE) -C audioprocess clean	
	$(MAKE) -C test-tools clean
	$(MAKE) -C libraries clean	

# -- new module creation
ifeq ($(NEW_MODULE_NAME),)
NEW_MODULE_NAME:=new_module
endif
NEW_MODULE_NAME_UPPER=$(shell echo $(NEW_MODULE_NAME) | tr a-z A-Z)
PATTERN:='s/empty_module_template/$(NEW_MODULE_NAME)/g; s/EMPTY_MODULE_TEMPLATE/$(NEW_MODULE_NAME_UPPER)/g'
SEDPRE:=sed -i -e $(PATTERN) modules/$(NEW_MODULE_NAME)/
MVTARGET:=echo $$file | sed -e $(PATTERN)
.PHONY: new_module
new_module:
	rm -fR modules/$(NEW_MODULE_NAME)
	make -C modules/empty_module_template clean
	cp -R modules/empty_module_template modules/$(NEW_MODULE_NAME)
	for file in c/empty_module_template.c c/empty_module_template.h c/makefile c/empty_module_template.mak matlab/empty_module_template.m test/empty_module_template_test.c test/empty_module_template_test.m test/makefile ; do \
		$(SEDPRE)$$file ; \
		mv modules/$(NEW_MODULE_NAME)/$$file modules/$(NEW_MODULE_NAME)/`$(MVTARGET)` ; \
	done
