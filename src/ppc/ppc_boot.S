.balign 4
.section .text

.global mp_reset_vector

mp_reset_vector:
	bl	.Laddr			/* get current address */
.Laddr:
	mflr	4			/* real address of .Laddr */
	lwz	0,(.Lstk-.Laddr)(4)	/* stack address location */
	mr	1,0			/* use user defined stack */

	addi	1,1,-4		/* make sure we don't overwrite debug mem */
	lis	0,0
	stw	0,0(1)		/* clear back chain */
	stwu	1,-64(1)		/* push another stack frame */
	
	/* Let her rip */

	bl 	mp_init_hw
	/* finally execute the firmware */
	bl	mp_start_exec
	/* return value from main is argument to exit */
	bl	mp_reset_vector

	trap


	
.Lstk:
/*	.long	__stack*/
	.long	stack_top

