global initGDT
extern gdtp ; kernel/gdt.c

; stack:
; [esp + 4] -> address to gdt struct (kernel/gdt.h @ struct gdt)
initGDT:
	lgdt [gdtp]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush ; far jump
.flush:
	ret