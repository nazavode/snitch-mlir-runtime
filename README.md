# MLIR for Snitch

Tools to build MLIR and LLVM IR sources for Snitch, and run them via Verilator.

* [`runtime/`](runtime/) - runtime support for specific dialects (e.g.: [`vector.print`](https://mlir.llvm.org/docs/Dialects/Vector/#vectorprint-vectorprintop))
* [GNU Make rules](Makefile.rules) to compile and link a mix of `.c` and `.ll` sources down to ELF static binaries that can be simulated.

## Prerequisites

Build tools in this folder assume that the [Verilator model](/hw/system/snitch_cluster/) has been successfully built.

## How To (via Docker image)

```shell
$ docker run -v <repo>:/src -ti ghcr.io/pulp-platform/snitch bash
# In container:
$ cd /src/mlir/example/echo
$ make run
```

**Note:** if the repository mount point is not `/src`, make sure to tell the Make rules about it:

```shell
$ make run SNITCH_RUNTIME_ROOT=/mymountpoint/sw/snRuntime
```
