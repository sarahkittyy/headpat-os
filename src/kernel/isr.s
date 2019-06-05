; For interrupt service routines with errors
%macro isr_err 1
global _isr_%1
_isr_%1:
	cli
	push %1 ; push interrupt ID
	jmp isr_stub
%endmacro

; For isrs without errors (push error code 0)
%macro isr_noerr 1
global _isr_%1
_isr_%1:
	cli
	push byte 0
	push %1 ; interrupt ID.
	jmp isr_stub
%endmacro

isr_noerr 0 ; div by 0
isr_noerr 1 ; debug
isr_noerr 2 ; non maskable exception
isr_noerr 3 ; bkpt
isr_noerr 4 ; into detected overflow
isr_noerr 5 ; oob exception
isr_noerr 6 ; invalid opcode
isr_noerr 7 ; no coprocessor
isr_err 8 ; double fault
isr_noerr 9 ; coprocessor segment overrun
isr_err 10 ; bad TSS
isr_err 11 ; segment not present
isr_err 12 ; stack fault
isr_err 13 ; general protection fault
isr_err 14 ; page fault
isr_noerr 15 ; unknown interrupt 
isr_noerr 16 ; coprocessor fault
isr_noerr 17 ; alignment check exception
isr_noerr 18 ; ignore
isr_noerr 19 ; vvv reserved exceptions
isr_noerr 20
isr_noerr 21
isr_noerr 22
isr_noerr 23
isr_noerr 24
isr_noerr 25
isr_noerr 26
isr_noerr 27
isr_noerr 28
isr_noerr 29
isr_noerr 30
isr_noerr 31
	
extern handleFault

; common isr functionality
isr_stub:
	pusha ; save state
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, handleFault
	call eax ; preserves `eip`
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8 ; cleans the pushed err code / isr #
	iret ; pops cs, eip, eflags, ss, and esp