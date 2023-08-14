#!/usr/bin/env python3

import re
import sys


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


def get_metadata_ids(ir):
    return (int(match.groups()[0]) for match in LLVM_NAMED_METADATA.finditer(ir))


if __name__ == "__main__":
    ir = sys.stdin.read()
    ir = re.sub(LLVM_TARGET_TRIPLE, "", ir)
    ir = re.sub(LLVM_TARGET_DATALAYOUT, "", ir)
    ir = re.sub(LLVM_ATTR_SIDEEFFECT, "", ir)
    ir = re.sub(LLVM_MODULE_FLAGS, "", ir)
    ir += f'target triple = "{SNITCH_TRIPLE}"\n'
    ir += f'target datalayout = "{SNITCH_DATALAYOUT}"\n'
    nmeta = max(get_metadata_ids(ir))
    module_meta = "!llvm.module.flags = !{ "
    for metaid, meta in enumerate(SNITCH_MODULE_METADATA, nmeta + 1):
        ir += f"!{metaid} = !{meta}\n"
        module_meta += f"!{metaid} "
    module_meta += "}\n"
    ir += module_meta
    print(ir)
