SNITCH_RUNTIME_THIS := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
include $(SNITCH_RUNTIME_THIS)/../Makefile.rules

%.o: %.c
	$(CC) $(CFLAGS) -I$(SNITCH_RUNTIME_THIS)/api -I$(SNITCH_RUNTIME_THIS)/src -c $< -o $@

libsnitch-runtime.a: snrt.o
	$(AR) rc $@ $^
	$(RANLIB) $@

all: libsnitch-runtime.a

clean:
	rm -f *.a *.o
