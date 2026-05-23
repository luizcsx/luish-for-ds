OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY {
    RAM_ARM9 (rwx) : ORIGIN = 0x02000000, LENGTH = 4M
}

SECTIONS {
    . = 0x02000000;
    
    .init : {
        KEEP(*(.init))
    } > RAM_ARM9

    .text : ALIGN(4) {
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
    } > RAM_ARM9

    .data : ALIGN(4) {
        *(.data)
        *(.data.*)
        . = ALIGN(4);
    } > RAM_ARM9

    .bss : ALIGN(4) {
        __bss_start = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } > RAM_ARM9
}
