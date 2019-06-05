#include "kernel/idt.h"

idt_entry idt[256];   /// The IDT.
idt_ptr idtp;		  /// The IDT Pointer.

void setIDTEntry(size_t num,
				 uint32_t base,
				 uint8_t flags)
{
	//Get a pointer to the idt entry.
	idt_entry* entry = &idt[num];

	//Set the base address
	entry->base_low  = base & 0xffff;
	entry->base_high = (base >> 16) & 0xffff;

	//Set the flags byte.
	entry->flags = flags;
	//Set the selector
	entry->selector = 0x08;

	//Set the reserved bytes.
	entry->reserved = 0;
}

void initIDT()
{
	//Sets up the IDT ptr.. See kernel/gdt.c
	idtp.limit = (sizeof(idt_entry) * 256) - 1;
	idtp.base  = (uint32_t)&idt;

	//Initialize the IDT to null.
	memset((void*)&idt, NULL, sizeof(idt_entry) * 256);

	//Flush the IDT.
	flushIDT();
}