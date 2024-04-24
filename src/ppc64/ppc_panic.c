/* -------------------------------------------

    Copyright Mahrouss Logic

------------------------------------------- */

#include <lib/boot.h>

/// BUGS: 0

/// @brief Goes into a panic state.
/// @param reason why?
void mp_panic(const char *reason)
{
    mp_put_string("KERNEL_PANIC: ");
    mp_put_string(reason);
    mp_put_char('\n');

    while (yes)
    {
        (void)0;
    }
}
