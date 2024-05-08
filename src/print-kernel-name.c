/* -------------------------------------------

    Copyright SoftwareLabs

------------------------------------------- */

#include <lib/boot.h>

/// @brief print the firmware name.
void mp_print_kernel_name(void)
{
#ifdef __COMPILE_POWERPC__
	mp_put_string(">> CoreBoot for POWER.\r\n");
#endif // __COMPILE_POWERPC__

#ifdef __COMPILE_AMD64__
	mp_put_string(">> CoreBoot for AMD64.\r\n");
#endif // __COMPILE_POWERPC__

#ifdef __COMPILE_RISCV__
	mp_put_string(">> CoreBoot for RISC-V.\r\n");
#endif // __COMPILE_POWERPC__
}
