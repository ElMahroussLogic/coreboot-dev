/* -------------------------------------------

    Copyright ZKA Web Services.

------------------------------------------- */

#ifndef __PARTITION_MAP_H__
#define __PARTITION_MAP_H__

#include <lib/boot.h>

/// @brief EPM GUID block.
typedef struct boot_guid
{
	uint32_t data1;
	uint16_t data2;
	uint16_t data3;
	uint8_t	 data4[8];
} boot_guid_t;

/* The first 0 > 128 addresses of a disk contains these headers. */

/**
 * @brief The EPM partition block.
 * used to represent a partition inside a media.
 */
struct __attribute__((packed)) part_block
{
	ascii_char_t magic[5];
	ascii_char_t name[32];
	boot_guid_t  uuid;
	int32_t		 version;
	int32_t		 num_blocks;
	int64_t		 lba_start;
	int64_t		 sector_sz;
	int64_t		 lba_end;
	int16_t		 type;
	int32_t		 fs_version;
	ascii_char_t fs[16]; /* ffs_2 */
	ascii_char_t reserved[401];
};

typedef struct part_block part_block_t;
typedef struct boot_block boot_block_t;

/* @brief AMD64 magic for EPM */
#define EPM_MAGIC_X86 "EPMAM"

/* @brief RISC-V magic for EPM */
#define EPM_MAGIC_RV "EPMRV"

/* @brief ARM magic for EPM */
#define EPM_MAGIC_ARM "EPMAR"

/* @brief 64x0 magic for EPM */
#define EPM_MAGIC_64X0 "EPM64"

/* @brief 32x0 magic for EPM */
#define EPM_MAGIC_32X0 "EPM32"

/* @brief POWER magic for EPM */
#define EPM_MAGIC_PPC "EPMPC"

/* @brief UEFI magic for EPM */
#define EPM_MAGIC_UEFI "EPMUE"

#define EPM_MAX_BLKS 128 /* 1 on UEFI EPM. */

#define EPM_BOOT_BLK_SZ sizeof(struct boot_block)
#define EPM_PART_BLK_SZ sizeof(struct part_block)

///! @brief variant enum.
///! use it in the boot block version field.
enum
{
	EPM_EMBEDDED_OS  = 0xcf,
	EPM_LINUX = 0x8f,
	EPM_BSD	  = 0x9f,
	EPM_NEWOS = 0x1f,
};

/// @brief Start of EPM headers.
/// @note There could be anything before this LBA.
/// Such as PC specific structures.
#define EPM_PART_BLK_START (0)

/// @brief EPM revision (actually at version 2)
#define EPM_REVISION (2U)

/// @brief EPM revision for UEFI (16)
#define EPM_REVISION_UEFI (0xF)

/// END SPECS

#endif // ifndef __PARTITION_MAP_H__
