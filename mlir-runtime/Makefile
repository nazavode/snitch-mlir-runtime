MLIR_RUNTIME_DIRNAME := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
include $(MLIR_RUNTIME_DIRNAME)/../Makefile.rules

OBJS = mlir-memref-alloc.o

CFLAGS += -I $(MLIR_RUNTIME_DIRNAME)/include

all: libmlir-runtime.a

libmlir-runtime.a: $(OBJS)
	$(AR) rc $@ $^
	$(RANLIB) $@

clean:
	rm -f *.a *.o
