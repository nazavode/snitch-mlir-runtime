#!/usr/bin/env python3

import re
import sys
import argparse

PARSER = argparse.ArgumentParser(
    prog="to-llvm12.py",
    description="""Transform an LLVM IR module to make it compatible with LLVM 12.
Reads from stdin, outputs to stdout.

Caveats:
* This applies textual changes, no parsing is involved, so your mileage may
  vary according to the input IR
* The input IR must use typed pointee pointers

Changes applied:
* Fix (or add if not present) the module target triple
* Fix (or add if not present) the module target data layout
* Remove backward incompatible side effects attributes on functions
* Fix (or add if not present) module flags specifying ABI and code model
""",
    formatter_class=argparse.RawDescriptionHelpFormatter,
)

LLVM_TARGET_TRIPLE = re.compile('target triple[\s]*=[\s]*"\w+"')
LLVM_TARGET_DATALAYOUT = re.compile('target datalayout[\s]*=[\s]*"\w+"')
LLVM_NAMED_METADATA = re.compile("!([\d]+)[\s]*=[\s]*!")
LLVM_MODULE_FLAGS = re.compile("!llvm.module.flags[\s]*=[\s]*.+")
LLVM_ATTR_SIDEEFFECT = re.compile("memory\(.*\)")


SNITCH_DATALAYOUT = "e-m:e-p:32:32-i64:64-n32-S128"
SNITCH_TRIPLE = "riscv32-unknown-unknown-elf"
SNITCH_MODULE_METADATA = [
    '{i32 1, !"wchar_size", i32 4}',
    '{i32 1, !"target-abi", !"ilp32d"}',
    '{i32 1, !"Code Model", i32 3}',
    '{i32 1, !"SmallDataLimit", i32 8}',
]


def get_availale_metadata_id(ir):
    return max(int(match.groups()[0]) for match in LLVM_NAMED_METADATA.finditer(ir)) + 1


if __name__ == "__main__":
    args = PARSER.parse_args()
    ir = sys.stdin.read()
    ir = re.sub(LLVM_TARGET_TRIPLE, "", ir)
    ir = re.sub(LLVM_TARGET_DATALAYOUT, "", ir)
    ir = re.sub(LLVM_ATTR_SIDEEFFECT, "", ir)
    ir = re.sub(LLVM_MODULE_FLAGS, "", ir)
    ir += f'target triple = "{SNITCH_TRIPLE}"\n'
    ir += f'target datalayout = "{SNITCH_DATALAYOUT}"\n'
    module_meta = "!llvm.module.flags = !{ "
    for metaid, meta in enumerate(SNITCH_MODULE_METADATA, get_availale_metadata_id(ir)):
        ir += f"!{metaid} = !{meta}\n"
        module_meta += f"!{metaid} "
    module_meta += "}\n"
    ir += module_meta
    print(ir)
