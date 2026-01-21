bits 32

section .text
    ALIGN 4
    dd 0x1BADB002
    dd 0x00000000
    dd -(0x1BADB002 - 0x00000000)


global _start
extern kernel_main

_start:
    cli
    mov esp, stack_space
    call kernel_main
    hlt
halt:
    cli
    hlt
    jmp halt


section .bss
resb 8192
stack_space:
