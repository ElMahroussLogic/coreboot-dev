/*
 *	========================================================
 *
 *	mp-unix
 * 	Copyright Mahrouss Logic, all rights reserved.
 * 	
 * 	========================================================
 */

#include <lib/types.h>
#include <stdarg.h>

#define FMT_NEW         '%'
#define FMT_NEWLINE     'n'
#define FMT_TABULATE    't'
#define FMT_FLOAT       'f'
#define FMT_STRING      's'
#define FMT_CHAR        'c'
#define FMT_INT         'i'
#define FMT_BOOLEAN     'b'
#define FMT_HEX         'x'

__COPYRIGHT("$core-boot$");

///////////////////////////////////////////////////////////////////////

/// @brief printf implementation, for CoreBoot.

///////////////////////////////////////////////////////////////////////

/* We still need these symbols */
#ifndef __x86_64__

/* No initialization needed */
void init_io(void) {}

void sys_print_str(caddr_t label)
{
    if (label == null ||
        *label == 0)
        return;

    mp_put_string(label);
}

#endif

static bool sys_runtime_check_number(size_t c)
{
    return c != ~0;
}

void sys_print_int(int64_t x)
{
    const char NUMBERS_ARRAY[17] = "0123456789ABCDEF";

    int y = x / 10;
    int d = x % 10;

    if (y) sys_print_int(y);

    /* same as below but for base-10 */
    if (d > 10)
    {
        sys_print_str("?");
        return;
    }
	
	if (d < 0)
		d = -d;
	
    char num[2];
	
	num[0] = NUMBERS_ARRAY[d];
    num[1] = '\0';

    sys_print_str(num);
}

void sys_print_hex(size_t x)
{
    const char NUMBERS_ARRAY[17] = "0123456789ABCDEF";

    int y = x / 16;
    int h = x % 16;

    if (y) sys_print_hex(y);
	
    /* fail if the hex number is not base-16 */
    if (h > 15) 
	{
        sys_print_str("?");
        return;
    }
	
	if (y < 0)
		y = -y;
	
    char num[2];
	
    num[0] = NUMBERS_ARRAY[h];
    num[1] = '\0';

    sys_print_str(num);
}

void sys_print_float(float_t num_x)
{		
	printf("%s%i.%i", num_x.sign ? "-" : " ", num_x.exponent, num_x.mantissa);
}

bool g_is_processing = false;

size_t printf(caddr_t fmt, ...)
{
    g_is_processing = true;
    va_list ap;

    bool fmt_enabled = false;
    size_t size = 0UL;

    va_start(ap, fmt);
    
    while (fmt[size] != '\0') 
    {
        switch (fmt[size]) 
        {
            case FMT_BOOLEAN: 
            {
                if (!fmt_enabled) goto putc;

                sys_print_str(va_arg(ap, int) > 0 ? "yes\r\n" : "no\r\n");

                fmt_enabled = false;
                break;
            }
			case FMT_FLOAT:
			{
                if (!fmt_enabled) goto putc;
                float_t arg = va_arg(ap, float_t);

                sys_print_float(arg);

                fmt_enabled = false;
				break;
			}
            case FMT_HEX: 
            {
                if (!fmt_enabled) goto putc;
                size_t arg = va_arg(ap, size_t);

                if (!sys_runtime_check_number(arg))
                    break;

                sys_print_str("0x");
                sys_print_hex(arg);

                fmt_enabled = false;
                break;
            }
            case FMT_INT: 
            {
                if (!fmt_enabled) goto putc;
                int num = va_arg(ap, int);

                if (!sys_runtime_check_number(num))
                    break;
				
				if (num < 0)
					sys_print_str("-");
	
                sys_print_int(num);

                fmt_enabled = false;
                break;
            }
            case FMT_TABULATE: 
            {
                if (!fmt_enabled) goto putc;

                sys_print_str("\t");

                fmt_enabled = false;
                break;
            }
            case FMT_NEWLINE: 
            {
                if (!fmt_enabled) goto putc;

                sys_print_str("\r\n");

                fmt_enabled = false;
                break;
            }
            case FMT_STRING: 
            {
                if (!fmt_enabled) goto putc;

                sys_print_str(va_arg(ap, caddr_t));

                fmt_enabled = false;
                break;
            }
            case FMT_NEW:
            {
                fmt_enabled = true;
                break;
            }
            case FMT_CHAR:
			{
                if (!fmt_enabled) goto putc;

                char chr = (char)va_arg(ap, int);
                mp_put_char(chr);
                break;
			}
            default:
            putc:
			{
				if (fmt_enabled)
					fmt_enabled = false;
				
                mp_put_char(fmt[size]);
                break;
			}
        }

        ++size;
    }
    va_end(ap);

    g_is_processing = false;
    return size;
}
