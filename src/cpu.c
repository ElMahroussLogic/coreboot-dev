/* -------------------------------------------

    Copyright Mahrouss Logic

------------------------------------------- */

#include <lib/types.h>

/// @brief Restarts the computer.
/// @param  
void mp_restart_machine(void) {
#ifdef __COMPILE_RISCV__
   volatile uint32_t* boardPower = 0x100000;
  *boardPower = 0x7777;
#endif
}
