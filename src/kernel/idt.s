global flushIDT
extern idtp ; kernel/idt.c

flushIDT:
	lidt [idtp]
	ret