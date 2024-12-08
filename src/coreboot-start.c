/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/mp-bit.h>
#include <lib/partition-map.h>
#include <lib/pci-tree.h>
#include <lib/boot.h>

/// BUGS: 0

/////////////////////////////////////////////////////////////////////////////////////////

// @name start.c //

// @brief Start file // This is where the firmware starts it's initialization //
// code. //

// @author Amlal EL Mahrouss //

/////////////////////////////////////////////////////////////////////////////////////////

extern void mp_append_scsi_tree(void);
extern void mp_append_video_tree(void);

extern void mp_start_context(uintptr_t);
extern void mp_start_rom(void);

extern int mp_boot_processor_ready;

/// @brief hardware thread counter.
uint64_t __mp_hart_counter = 0UL;

/// @brief Start executing the firmware.
/// @param
void mp_start_exec(void)
{
	++__mp_hart_counter;

	uintptr_t hart = __mp_hart_counter;

	mp_sync_synchronize();

	// let the hart 0 init our stuff.
	if (hart == 1)
	{
		mp_put_string(">> Welcome to CoreBoot, (c) Amlal EL Mahrouss. Built the ");
		mp_put_string(__DATE__);
		mp_put_string("\r\r\n");

#ifdef __COMPILE_POWERPC__
		mp_put_string(">> CPU: POWER64.\r\r\n");
#endif // __COMPILE_POWERPC__

#ifdef __COMPILE_AMD64__
		mp_put_string(">> CPU: AMD64.\r\r\n");
#endif // __COMPILE_AMD64__

#ifdef __COMPILE_ARM64__
		mp_put_string(">> CPU: ARM64.\r\r\n");
#endif // __COMPILE_ARM64__

#ifdef __COMPILE_ARM32__
		mp_put_string(">> CPU: ARM32.\r\r\n");
#endif // __COMPILE_ARM64__

#ifdef __COMPILE_RISCV__
		mp_put_string(">> CPU: RISC-V.\r\r\n");
#endif // __COMPILE_RISCV__
	}

	/// @brief Boots here if LX header matches what we except.

	volatile struct mp_boot_header* boot_hdr =
		(volatile struct mp_boot_header*)(SYS_BOOT_ADDR);

	/**
      boot if:
          - ident matches.
          - version matches.
  */

	if (boot_hdr->h_mag[0] == SYS_BOOT_MAG_0 &&
		boot_hdr->h_mag[1] == SYS_BOOT_MAG_1)
	{
		if (boot_hdr->h_revision != SYS_BOOT_VER)
		{
			if (hart == 1)
			{
				mp_put_string(">> Can't Boot the second ROM, trying the disk... (CB0003)\r\n");
			}
		}
		else
		{
			if (hart == 1)
			{
				mp_put_string(">> Switch to ROM: ");
				mp_put_string((const char*)boot_hdr->h_name);
				mp_put_char('\r');
				mp_put_char('\n');

				// printf(">> address: %x\n", boot_hdr->h_start_address);
			}

			if (boot_hdr->h_start_address != 0)
			{
				mp_boot_processor_ready = 1;
				mp_start_context(boot_hdr->h_start_address);
			}

			mp_put_string(">> ROM returned? (CB0002)\r\n");
		}
	}
	else
	{
		if (hart == 1)
		{
			mp_put_string(">> Can't boot ROM. (CB0001)\r\n");
		}
	}

	/// TODO: boot from EPM here

	/// end of TODO

	if (hart > 1)
	{
		while (1)
		{
			if (__mp_hart_counter == 0)
			{
				mp_restart_machine();
				return;
			}
		}
	}

#ifndef __COMPILE_ARM64__
	/// since context isnt present on disk or any removable media, we can run this
	/// tiny shell now.
	while (yes)
	{
		char buf[255] = "\0";

		size_t bufSz = 0;

		mp_put_string("# ");

		char ch = mp_get_char();

		while (ch != 0xD)
		{
			if (ch == 127)
			{
				buf[bufSz] = 0;

				if (bufSz > 0)
				{
					--bufSz;
					mp_put_string("\033[D");
				}

				ch = mp_get_char();
				continue;
			}
			else
			{
				mp_put_char(ch);
			}

			if (ch != 127)
			{
				switch (ch)
				{
				case '\\': {
					mp_put_char('\r');
					mp_put_char('\n');
					mp_put_char('\t');
					break;
				}
				default:
					break;
				}

				buf[bufSz] = ch;
				++bufSz;
			}

			if (bufSz > 255)
				ch = 0xD;
			else
				ch = mp_get_char();
		}

		mp_put_string("\r\n");

		if (strcmp(buf, "uname") == 0)
		{
			mp_print_name();
		}
		else if (strcmp("echo ", buf) == 0)
		{
			mp_put_string(buf + strlen("echo "));
			mp_put_string("\r\n");
		}
		else if (strcmp("boot ", buf) == 0)
		{
			char* bootDevice = buf + strlen("boot ");

			if (bootDevice[0] != 0)
			{
				mp_put_string(">> Booting from ");
				mp_put_string(bootDevice);
				mp_put_string("...\r\n");

				goto cb_restart_label;
			}
		}
		else if (strcmp("clear", buf) == 0)
		{
			mp_put_string("\033[2J");
			mp_put_string("\033[0;0H"); /* set cursor to 0:0 */
		}
		else if (strcmp("reset", buf) == 0)
		{
		cb_restart_label:
			__mp_hart_counter = 0UL; // to make sure that we try again.
			mp_restart_machine();	 // now restart the machine.

			return; // if it doesnt work on your platform, this will jump back to the
					// reset vector.
		}
		else
		{
			mp_put_string(">> Syntax error: ");
			mp_put_string(*buf == 0 ? "empty input." : buf);
			mp_put_string("\r\n");
		}
	}
#else
	while (yes)
	{
		asm volatile("hlt #0");
	}
#endif
}
