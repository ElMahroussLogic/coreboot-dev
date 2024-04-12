/* -------------------------------------------

    Copyright Mahrouss Logic

------------------------------------------- */

/**
 * @file scsi-backend-ppc.cc
 * @author Amlal El Mahrouss (amlal@el-mahrouss-logic.com)
 * @brief PowerPC Disk support, via SCSI.
 * @version 0.2
 * @date 2024-01-16
 *
 * @copyright Copyright (c) 2024, Mahrouss Logic.
 *
 */

#include <lib/pci-tree.h>
#include <lib/types.h>
#include <lib/pci-tree.h>

#define MP_SCSI_BASE_ADDRESS (0xFE008004) /* PCI base for SCSI drives */
#define MP_SCSI_DRIVER_NAME  ("@scsi-drive") /* generic scsi device, required */
#define MP_SCSI_STRIDE       (0x1000)

/// BUGS: 0

/// @brief SCSI support for PowerPC.

void mp_append_scsi_tree(void)
{
	mp_pci_append_tree(MP_SCSI_DRIVER_NAME, MP_SCSI_BASE_ADDRESS, 0x0);
}
