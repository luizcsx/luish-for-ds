.arm
.section .init
.global _start

_start:
    mov r0, #0x12
    msr cpsr_c, r0
    mov sp, #0x02000000
    add sp, sp, #0x00400000

    mov r0, #0x1F
    msr cpsr_c, r0
    mov sp, #0x02000000
    add sp, sp, #0x003F0000

    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r2, #0
.clear_bss:
    cmp r0, r1
    strlo r2, [r0], #4
    blo .clear_bss

    ldr r0, =main
    bx r0
