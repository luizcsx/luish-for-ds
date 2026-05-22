OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY {
    RAM_ARM9 (rwx) : ORIGIN = 0x02000000, LENGTH = 4M
}

SECTIONS {
    . = 0x02000000;
    
    .init : {
        *(.init)
    } > RAM_ARM9

    .text : {
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata.*)
    } > RAM_ARM9

    .data : {
        *(.data)
        *(.data.*)
    } > RAM_ARM9

    .bss : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    } > RAM_ARM9
}
