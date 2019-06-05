#include "kernel/gdt.h"

gdt_entry gdt[3];
gdt_ptr gdtp;

void setGDTEntry(size_t num,
				 uint32_t base,
				 uint32_t limit,
				 uint8_t access,
				 uint8_t gran)
{
	gdt_entry* entry   = &gdt[num];
	entry->base_low	= base & 0xffff;
	entry->base_middle = (base >> 16) & 0xff;
	entry->base_high   = (base >> 24) & 0xff;

	entry->limit_low   = limit & 0xffff;
	entry->granularity = (limit >> 16) & 0x0f;

	entry->granularity |= gran & 0xf0;
	entry->access = access;
}

void initGDT()
{
	/*
	 * Steps:
	 * 1) Write values into the GDT.
	 * 2) Set the gdt pointer (gdtp).
	 * 3) Call initGDT with the address to the gdt pointer.
	 */
	gdtp.limit = (sizeof(gdt_entry) * 3) - 1;
	gdtp.base  = (uint32_t)&gdt;

	//Null descriptor
	setGDTEntry(0, 0, 0, 0, 0);

	/*
	 * Code segment
	 * Base addr of 0,
	 * Limit of 4 GB,
	 * 4 KB Granularity.
	 * 32-bit opcodes
	 */
	setGDTEntry(1, 0, 0xFFFFFFFF, 0b10011010, 0b11001111);

	/*
	 * Data segment
	 * Same as the code segment, but the descriptor type in the access
	 * byte says it's a data segment
	 */
	setGDTEntry(2, 0, 0xFFFFFFFF, 0b10010010, 0b11001111);

	//Flush the GDT.
	flushGDT();
}