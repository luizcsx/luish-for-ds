.arm
.section .text
.global _start

_start:
    mov r0, #0x03000000
    add r0, r0, #0x00004000
    mov sp, r0
    bl main

loop:
    b loop
