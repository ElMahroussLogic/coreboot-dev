/* -------------------------------------------

    Copyright Mahrouss Logic

------------------------------------------- */

/**
 * @file audio-backend-ppc.cc
 * @author Amlal El Mahrouss (amlal@el-mahrouss-logic.com)
 * @brief Audio support.
 * @version 0.2
 * @date 2024-01-16
 *
 * @copyright Copyright (c) 2024, Mahrouss Logic.
 *
 */

#include <lib/pci-tree.h>
#include <lib/types.h>

#define MP_AHCI_BASE_ADDRESS (0xFE008004)  // 4M
#define MP_AHCI_DRIVER_NAME ("@sound")

/// BUGS: 0
