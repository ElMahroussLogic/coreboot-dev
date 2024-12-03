/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/boot.h>

/// @brief Restarts the computer.
/// @param none.
void mp_restart_machine(void)
{
#ifdef __COMPILE_RISCV__
	volatile uint32_t* boardPower = (volatile uint32_t*)0x100000;
	*boardPower					  = 0x7777;

	while (1)
	{
		asm volatile("wfi");
	}
#endif
}
