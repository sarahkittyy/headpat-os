; macro for generating interrupt requests.
%macro irq 1
global _irq_%1
_irq_%1:
	cli
	push byte 0 ; dummy error code
	push byte %1 + 32 ; irq mapping 0-15 to 32-47
	jmp _irq_common
%endmacro

irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15

; irq.c
extern handleIRQ	

; similar to isr_common
_irq_common:
	pusha
	push ds
	push es
	push fs,
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, handleIRQ 
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret