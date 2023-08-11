# Minimal MLIR Runtime for Snitch

Minimal runtime support for lowering of various MLIR dialects (mainly
[`llvm`](https://mlir.llvm.org/docs/Dialects/LLVM/),
[`vector`](https://mlir.llvm.org/docs/Dialects/Vector/) and
[`memref`](https://mlir.llvm.org/docs/Dialects/MemRef/)).

This has been built via:

* a direct port of the
  [MLIR execution engine utils](https://github.com/llvm/llvm-project/blob/55c88aafa6965646d46404eab16393ba8b1bff95/mlir/include/mlir/ExecutionEngine/CRunnerUtils.h)
  to the Snitch runtime and toolchains; 
* shims to make the
  [MLIR LLVM IR Target](https://mlir.llvm.org/docs/TargetLLVMIR/#generic-alloction-and-deallocation-functions)
  happy;
* shims to make
  [`vector.print`](https://mlir.llvm.org/docs/Dialects/Vector/#vectorprint-mlirvectorprintop)
  work;
* allocators to allow using STL containers on Snitch (currently leveraging bump allocators provided by the runtime).

## Usage

The runtime library can be compiled as follows:

    mkdir build
    cd build
    cmake ..
    make

The tests can be executed as follows:

    make test

Interesting CMake options that can be set via `-D<option>=<value>`:

- `SNITCH_BANSHEE`: The banshee simulator binary to use for test execution.
- `CMAKE_TOOLCHAIN_FILE`: The compiler toolchain configuration to use. Acceptable values:
    - `toolchain-gcc` for a GNU tolchain
    - `toolchain-llvm` for a LLVM/Clang toolchain (coming soon)
    - Your own custom `<toolchain>.cmake` file; see `../cmake/toolchain-gcc.cmake` for reference