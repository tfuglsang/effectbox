default: metrics signals fopnchk

.PHONY: metrics
metrics:
	$(MAKE) -C metrics
.PHONY: fopnchk
fopnchk:
	$(MAKE) -C c/fopnchk

.PHONY: signals
signals: 
	$(MAKE) -C signals

.PHONY: clean
clean:
	$(MAKE) -C metrics clean
	$(MAKE) -C signals clean
	$(MAKE) -C c/fopnchk clean
