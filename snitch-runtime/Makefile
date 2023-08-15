SNITCH_RUNTIME_DIRNAME := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
include $(SNITCH_RUNTIME_DIRNAME)/../Makefile.rules

OBJS =
OBJS += alloc.o
OBJS += barrier.o
OBJS += dma.o
OBJS += interrupt.o
OBJS += memcpy.o
OBJS += perf_cnt.o
OBJS += printf.o
OBJS += putchar.o
OBJS += ssr.o
OBJS += ssr_v2.o
OBJS += start.o
OBJS += team.o
OBJS += start_snitch_rtl.o

CFLAGS += -I $(SNITCH_RUNTIME_DIRNAME)/include
CFLAGS += -I $(SNITCH_RUNTIME_DIRNAME)/vendor/riscv-opcodes

all: libsnitch-runtime.a

libsnitch-runtime.a: $(OBJS)
	$(AR) rc $@ $^
	$(RANLIB) $@

clean:
	rm -f *.a *.o

