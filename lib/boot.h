/* -------------------------------------------

    Copyright Mahrouss Logic

------------------------------------------- */

#pragma once

///
/// @file types.h
/// @brief CoreBoot types, data structures, and standard library.
///

typedef __UINTPTR_TYPE__ uintptr_t;
typedef __UINT32_TYPE__	 phys_addr_t;

typedef unsigned long ulong_t;

typedef unsigned long long int uint64_t;
typedef unsigned			   uint32_t;
typedef unsigned short		   uint16_t;
typedef unsigned char		   uint8_t;

#ifdef __unix__
#undef __unix__
#define __unix__ 7
#endif // !__unix__

#define __mpboot__ __unix__

typedef __INTPTR_TYPE__ intptr_t;

typedef __INT64_TYPE__ int64_t;
typedef int			   int32_t;
typedef short		   int16_t;
typedef char		   int8_t;

typedef void*		voidptr_t;
typedef char*		addr_t;
typedef const char* caddr_t;

typedef __UINTPTR_TYPE__ ptrtype_t;
typedef ptrtype_t		 size_t;

#define mp_sync_synchronize() __sync_synchronize()
#define array_size(arr)		  (sizeof(arr[0]) / sizeof(arr))

#ifndef nil
#define nil ((voidptr_t)0)
#endif // ifndef nil

#ifndef null
#define null ((voidptr_t)0)
#endif // ifndef null

#define __no  0
#define __yes 1

#define boolean char

#define no	__no
#define yes __yes

#ifndef __cplusplus
#define bool boolean
#define false no
#define true yes
#endif //!_cplusplus

#define SYS_RESTART	 0
#define SYS_SHUTDOWN 1

#define __COPYRIGHT(s) /* unused */

#ifdef __COMPILE_RISCV__
#define SYS_BOOT_ADDR		 (0x80020000)
#define SYS_BOOT_ADDR_STR	 "0x80020000"
#define SYS_FRAMEBUFFER_ADDR 0x40000000L
#elif defined(__COMPILE_POWERPC__)
#define SYS_BOOT_ADDR		 0x1030000
#define SYS_BOOT_ADDR_STR	 "0x1030000"
#define SYS_FRAMEBUFFER_ADDR 0x40000000L
#else
#define SYS_BOOT_ADDR		 0x1030000
#define SYS_BOOT_ADDR_STR	 "0x1030000"
#define SYS_FRAMEBUFFER_ADDR 0x40000000L
#endif // ifndef __COMPILE_POWERPC__

#define SYS_UART_BASE 0x10000000

#define SYS_BAUDRATE_TABLE                                            \
	{                                                                 \
		300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 \
	}

#define SYS_STRING(s) #s

#define SYS_BOOT_MAG_0 'C'
#define SYS_BOOT_MAG_1 'B'

#define SYS_BOOT_VER 0x101

#define SYS_BOOT_CALL(struct, offset)                      \
	mp_proc_t proc_##offset = (mp_proc_t)(struct->offset); \
	proc_##offset();

/// @brief float type.
typedef union {
	struct
	{
		char  sign;
		int	  mantissa;
		short exponent;
	};

	float f;
} float_t;

/// \brief UTF-32 character
typedef uint32_t utf_char_t;

/// @brief panic the entire system.
/// @param reason why text.
void mp_panic(const char* reason);

/// @brief update the power status of the machine.
void mp_update_power_status(boolean restart);

/// @brief puts a string in serial
/// @param text
/// @return
size_t mp_put_string(const char* text);

/// @brief gets a char from serial
/// @param
/// @return
utf_char_t mp_get_char(void);

/// @brief puts a char in serial
/// @param ch
void mp_put_char(utf_char_t ch);

/// @brief Hangs the firmware.
/// @param void no args.
void mp_restart_machine(void);

/// @brief Flushs the TLB.
/// @param void no args.
void mp_flush_tlb(void);

/// @brief Print current kernel name.
/// @param
void mp_print_kernel_name(void);

/// @brief String length getter
/// @param str the string.
/// @return
size_t strlen(caddr_t str);

/// @brief Compare two strings.
/// @param src source string
/// @param cmp string to compare.
/// @return
size_t strcmp(caddr_t src, caddr_t cmp);

typedef void (*mp_proc_t)();

/// \brief ASCII character.
typedef char ascii_char_t;

/// @brief Linear Executable Header
/// @author Amlal El Mahrouss
struct __attribute__((aligned(4))) mp_boot_header
{
	const ascii_char_t h_mag[2];		// magic number
	const ascii_char_t h_name[10];		// operating system name
	const uint32_t	   h_revision;		// firmware revision
	const uint64_t	   h_start_address; // start address (master/slave thread)
};

/// @brief Check if filesystem exists.
/// @param fs Filesystem identifier.
boolean mp_filesystem_exists(caddr_t fs);

// EOF.