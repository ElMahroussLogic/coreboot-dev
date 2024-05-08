/* -------------------------------------------

    Copyright SoftwareLabs

------------------------------------------- */

.balign 4
.global __start
 
__start
	mv sp, __mp_stack_end

	/* don't care about page_zero, it's gonna be a raw binary */

    b mp_start_exec