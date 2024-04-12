ENTRY(mp_reset_vector)
SECTIONS
{
  . = 0xf00000; 

 .startup . : { ppc_boot.o(.text) }
 .text : { *(.text) }
 .data : { *(.data) }
 .bss : { *(.bss COMMON) }
 . = ALIGN(8);
 . = . + 0x1000; /* 4kB of stack memory */
 stack_top = .;
 
 PROVIDE(mp_memory_end = .);
}
