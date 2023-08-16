# Example makefile
# By including 'Makefile.rules', proper rules for .ll, .c and for building the
# runtime are in place, the only missing thing we have to deal with here is
# the actual dependencies of the final target

include ../../Makefile.rules

OBJS =
OBJS += echo.o
OBJS += main.o

SNITCH_RUNTIME_LIB = ../../snitch-runtime/libsnitch-runtime.a

CFLAGS += -I../../snitch-runtime/include
CFLAGS += -Wall -Wextra -pedantic -Wno-language-extension-token -Wno-gnu-statement-expression

echo.x: $(OBJS)
	$(LD) $(LDFLAGS) $(SNITCH_RUNTIME_LIB) $^ -o $@

run: echo.x
	/opt/bin/snitch_cluster.vlt $<

clean:
	rm -f *.o *.a *.ll12 echo.x
