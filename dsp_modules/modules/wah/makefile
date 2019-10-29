.DEFAULT: c
.PHONY: c
c:
	make -C c

.PHONY: test
test: c
	make -C test

.PHONY: matlab
matlab:
	make -C test matlab

clean:
	make -C test clean
	make -C c clean