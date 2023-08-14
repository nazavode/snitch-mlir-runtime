MLIR_RUNTIME_THIS := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
include $(MLIR_RUNTIME_THIS)/../Makefile.rules

libmlir-runtime.a: mlir-memref-alloc.o
	$(AR) rc $@ $^
	$(RANLIB) $@

all: libmlir-runtime.a

clean:
	rm -f *.a *.o
