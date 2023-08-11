#include "mlir-memref.h"

#include <stdint.h>
#include <alloc_decls.h>

//===----------------------------------------------------------------------===//
// Support library for the LLVM IR Target. See:
// https://mlir.llvm.org/docs/TargetLLVMIR/#generic-alloction-and-deallocation-functions
//===----------------------------------------------------------------------===//

void *_mlir_memref_to_llvm_alloc(size_t size) {
  return snrt_l1alloc(size);
}

void _mlir_memref_to_llvm_free(void *ptr) {
  // For the current Snitch Runtime bump allocator,
  // free is a no-op.
}

