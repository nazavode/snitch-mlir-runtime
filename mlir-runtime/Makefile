CC = /tools/riscv-llvm/bin/riscv32-unknown-elf-clang
AR = /tools/riscv-llvm/bin/llvm-ar
RANLIB = /tools/riscv-llvm/bin/llvm-ranlib

CFLAGS =
CFLAGS += -mcpu=snitch
CFLAGS += -mcmodel=medany
CFLAGS += -ffast-math
CFLAGS += -fno-builtin-printf
CFLAGS += -fno-common
CFLAGS += -ffunction-sections
CFLAGS += -static
CFLAGS += -mllvm -enable-misched=false
CFLAGS += -mno-relax
CFLAGS += -menable-experimental-extensions
CFLAGS += -O3
CFLAGS += -Wall -Wextra -pedantic

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libmlir-runtime.a: mlir-memref-alloc.o
	$(AR) rc $@ $^
	$(RANLIB) $@

all: libmlir-runtime.a

clean:
	rm -f *.a *.o
