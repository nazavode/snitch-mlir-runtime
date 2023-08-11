// Copyright 2023 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#define CLUSTER_TCDM_BASE_ADDR 0x10000000
#define CLUSTER_PERIPH_BASE_ADDR (CLUSTER_TCDM_BASE_ADDR + 0x20000)
#define CLUSTER_ZERO_MEM_START_ADDR (CLUSTER_PERIPH_BASE_ADDR + 0x10000)
#define CLUSTER_ZERO_MEM_END_ADDR (CLUSTER_ZERO_MEM_START_ADDR + 0x10000)
#define CLINT_BASE_ADDR 0xffff0000
