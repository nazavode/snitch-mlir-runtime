# Example makefile
# By including 'Makefile.rules', proper rules for .ll, .c and for building the
# runtime are in place, the only missing thing we have to deal with here is
# the actual dependencies of the final target

include ../../Makefile.rules

addf.x: addf.o main-snitch.o mlir-memref.o $(SNITCH_RUNTIME_LIB)
	$(SNITCH_LD) $(LDFLAGS) $(SNITCH_RUNTIME_LIB) $^ -o $@

run: addf.x
	/opt/bin/snitch_cluster.vlt $<

clean: clean-snitch-runtime
	rm -f addf.o main-snitch.o mlir-memref.o addf.x

logs/trace_hart_%.txt: logs/trace_hart_%.dasm /src/util/gen_trace.py
	spike-dasm < $< | $(PYTHON) /src/util/gen_trace.py > $@

traces: $(shell (ls logs/trace_hart_*.dasm 2>/dev/null | sed 's/\.dasm/\.txt/') || echo "")
