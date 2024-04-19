/* -------------------------------------------

    Copyright Mahrouss Logic

------------------------------------------- */

#include <lib/types.h>

/// @brief print kernel/firmware name.
/// @param
void mp_print_kernel_name(void) {
#ifdef __COMPILE_POWERPC__
    mp_put_string(">> CoreBoot for POWER.\r\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_RISCV__
    mp_put_string(">> CoreBoot for RISC-V.\r\r\n");
#endif  // __COMPILE_POWERPC__
}
