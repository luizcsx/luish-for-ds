OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
    . = 0x02000000;
    .text : { crt0.o(.text) *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss) }
}
