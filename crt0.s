@ ==============================================================================
@ Luish Kernel - System Architecture Boot Vector (crt0.s)
@ ==============================================================================

.section .init
.global _start
.arm

_start:
    @ NDS Hardware Header Area - Reserved space required by BIOS/Emulator
    b     reset_vector      @ Jump over the header metadata space
    .space 0x15C            @ Fill the official NDS header structural gap

reset_vector:
    @ Disable interrupts and set up the ARM9 Stack Pointer in DTCM memory
    mov     r0, #0xD3       @ Switch to Supervisor Mode (SVC) with IRQ/FIQ disabled
    msr     cpsr_c, r0
    ldr     sp, =0x027FF000 @ Set stack pointer to the safe top area of main RAM

    @ Clear the BSS memory segment before invoking the main C code
    ldr     r0, =__bss_start
    ldr     r1, =__bss_end
    mov     r2, #0
clear_bss_loop:
    cmp     r0, r1
    strlo   r2, [r0], #4
    blo     clear_bss_loop

    @ Hand over total execution control to the main C function kernel
    ldr     r0, =main
    bx      r0

.global __bss_start
.global __bss_end
