/* -------------------------------------------

    Copyright Mahrouss Logic

------------------------------------------- */

#include <lib/types.h>

/// @brief 
/// @param  
void mp_print_kernel_name(void) {
#ifdef __COMPILE_POWERPC__
    mp_put_string(">> NeWS PowerPC CoreBoot.\r\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_RISCV__
    mp_put_string(">> NeWS RISC-V CoreBoot.\r\r\n");
#endif  // __COMPILE_POWERPC__
}
