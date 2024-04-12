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

#define MP_PCI_DRIVER_OFFSET (0xFE008004)
#define MP_PCI_DRIVER_NAME ("@vbe-display")

/// BUGS: 0

/// @brief Initialize framebuffer.
void mp_append_video_tree(void) {
	mp_pci_append_tree(MP_PCI_DRIVER_NAME, MP_PCI_DRIVER_OFFSET, 0x0);
}
