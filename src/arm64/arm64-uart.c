/* -------------------------------------------

    Copyright ZKA Web Services.

------------------------------------------- */

#include <lib/boot.h>
#include <lib/string.h>

/// BUGS: 0

/* this file handles the UART */

static uint32_t* mp_uart_ptr = (uint32_t*)SYS_UART_BASE;

utf_char_t mp_get_char(void)
{
	uintptr_t ptr = SYS_UART_BASE;
	while (!(*(((volatile uint32_t*)ptr) + 0x18) & 0x01))
		;

	return (utf_char_t)*mp_uart_ptr;
}

// we need that one, to avoid sending mutliple chars to UART.
static boolean mp_locked_put_char = no;

void mp_put_char(utf_char_t ch)
{
	while (mp_locked_put_char)
	{
	
	}

	mp_locked_put_char = yes;
	*mp_uart_ptr	   = ch;
	mp_locked_put_char = no;
}

/// @brief UART put string
/// @param text the input text.
size_t mp_put_string(const char* text)
{
	if (text == nil)
		return 0;

	size_t i = 0;

	for (; i < strlen(text); i++)
	{
		mp_put_char(text[i]);
	}

	return i;
}
