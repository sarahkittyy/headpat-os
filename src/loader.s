global loader

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ (1 << 0) | (1 << 1)
CHECKSUM equ (0 - (FLAGS + MAGIC_NUMBER))
KERNEL_STACK_SIZE equ 4096

section .multiboot
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .text:
align 4
loader:
	mov esp, kernel_stack + KERNEL_STACK_SIZE
	
	extern kmain
	call kmain
	
.loop:
	jmp .loop

section .bss:
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE