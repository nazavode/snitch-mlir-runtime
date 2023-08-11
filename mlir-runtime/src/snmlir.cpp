#include "snmlir.h"

#include <printf.h> // note: this is Snitch's own printf shim, *not* the std one
#include <snrt.h>

//===----------------------------------------------------------------------===//
// Defined by the actual platform (e.g.: Banshee)
//===----------------------------------------------------------------------===//

extern "C" void snrt_putchar(char);

//===----------------------------------------------------------------------===//
// Shims for missing libc
//===----------------------------------------------------------------------===//

static inline void *snrt_alloca(size_t size) {
  return __builtin_alloca(size);
}

//===----------------------------------------------------------------------===//
// Support library for the LLVM IR Target. See:
// https://mlir.llvm.org/docs/TargetLLVMIR/#generic-alloction-and-deallocation-functions
//===----------------------------------------------------------------------===//

extern "C" void *_mlir_memref_to_llvm_alloc(size_t size) {
  return ::snrt_l1alloc(size);
}

extern "C" void _mlir_memref_to_llvm_free(void *ptr) {
  // For the current Snitch Runtime bump allocator,
  // free is a no-op.
}

//===----------------------------------------------------------------------===//
// Small runtime support library for vector.print lowering during codegen.
//===----------------------------------------------------------------------===//

extern "C" void printI64(int64_t i) { printf("%lld", i); }

extern "C" void printU64(uint64_t u) { printf("%llu", u); }

extern "C" void printF32(float f) { printf("%g", f); }

extern "C" void printF64(double d) { printf("%lg", d); }

extern "C" void printOpen() {
  ::snrt_putchar('(');
  ::snrt_putchar(' ');
}

extern "C" void printClose() {
  ::snrt_putchar(' ');
  ::snrt_putchar(')');
}

extern "C" void printComma() {
  ::snrt_putchar(',');
  ::snrt_putchar(' ');
}

extern "C" void printNewline() { ::snrt_putchar('\n'); }

//===----------------------------------------------------------------------===//
// Small runtime support library for memref.copy lowering during codegen.
//===----------------------------------------------------------------------===//

extern "C" void memrefCopy(int64_t elemSize, UnrankedMemRefType<char> *srcArg,
                           UnrankedMemRefType<char> *dstArg) {
  DynamicMemRefType<char> src(*srcArg);
  DynamicMemRefType<char> dst(*dstArg);

  int32_t rank = src.rank;
  // MLIR_MSAN_MEMORY_IS_INITIALIZED(src.sizes, rank * sizeof(int32_t));

  // Handle empty shapes -> nothing to copy.
  for (int rankp = 0; rankp < rank; ++rankp)
    if (src.sizes[rankp] == 0)
      return;

  char *srcPtr = src.data + src.offset * elemSize;
  char *dstPtr = dst.data + dst.offset * elemSize;

  if (rank == 0) {
    ::snrt_memcpy(dstPtr, srcPtr, elemSize);
    return;
  }

  int32_t *indices =
      static_cast<int32_t *>(::snrt_l1alloc(sizeof(int32_t) * rank));
  int32_t *srcStrides =
      static_cast<int32_t *>(::snrt_l1alloc(sizeof(int32_t) * rank));
  int32_t *dstStrides =
      static_cast<int32_t *>(::snrt_l1alloc(sizeof(int32_t) * rank));

  // Initialize index and scale strides.
  for (int rankp = 0; rankp < rank; ++rankp) {
    indices[rankp] = 0;
    srcStrides[rankp] = /* src.strides[rankp] */ 1 * elemSize;
    dstStrides[rankp] = /* dst.strides[rankp] */ 1 * elemSize;
  }

  int32_t readIndex = 0, writeIndex = 0;
  for (;;) {
    // Copy over the element, byte by byte.
    ::snrt_memcpy(dstPtr + writeIndex, srcPtr + readIndex, elemSize);
    // Advance index and read position.
    for (int32_t axis = rank - 1; axis >= 0; --axis) {
      // Advance at current axis.
      auto newIndex = ++indices[axis];
      readIndex += srcStrides[axis];
      writeIndex += dstStrides[axis];
      // If this is a valid index, we have our next index, so continue copying.
      if (src.sizes[axis] != newIndex)
        break;
      // We reached the end of this axis. If this is axis 0, we are done.
      if (axis == 0)
        return;
      // Else, reset to 0 and undo the advancement of the linear index that
      // this axis had. Then continue with the axis one outer.
      indices[axis] = 0;
      readIndex -= src.sizes[axis] * srcStrides[axis];
      writeIndex -= dst.sizes[axis] * dstStrides[axis];
    }
  }
}