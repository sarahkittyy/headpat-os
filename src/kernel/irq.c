#include "kernel/irq.h"

#define externIRQ(x) void _irq_##x()
externIRQ(0);
externIRQ(1);
externIRQ(2);
externIRQ(3);
externIRQ(4);
externIRQ(5);
externIRQ(6);
externIRQ(7);
externIRQ(8);
externIRQ(9);
externIRQ(10);
externIRQ(11);
externIRQ(12);
externIRQ(13);
externIRQ(14);
externIRQ(15);

/// Function pointers to IRQ handlers for specific IRQs.
void* irq_routines[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0};

/*
 * PIC INTERRUPTS:
 * 0 Timer
 * 1 Keyboard
 * 2 PIC2
 * 3 COM2
 * 4 COM1
 * 5 LPT 2
 * 6 Floppy Disk
 * 7 LPT 1
 * 8 RTC
 * 9 General i/o
 * 10 general i/o
 * 11 general i/o
 * 12 general i/o
 * 13 coprocessor
 * 14 IDE Bus
 * 15 IDE Bus
 */

void installIRQ(size_t number, void (*handler)(FaultData*))
{
	//Set the IRQ.
	irq_routines[number] = handler;
}

void removeIRQ(size_t number)
{
	//Nullify the IRQ.
	irq_routines[number] = NULL;
}

/**
 * @brief Move IRQs 0-15 to 32-47
 * 
 */
void remapIRQ()
{
	outbyte(0x20, 0x11);
	outbyte(0xA0, 0x11);
	outbyte(0x21, 0x20);
	outbyte(0xA1, 0x28);
	outbyte(0x21, 0x04);
	outbyte(0xA1, 0x02);
	outbyte(0x21, 0x01);
	outbyte(0xA1, 0x01);
	outbyte(0x21, 0x0);
	outbyte(0xA1, 0x0);
}

//Maps the IRQ to an entry in the IDT.
#define mapIRQtoIDT(x) setIDTEntry(x + 32, (uint32_t)_irq_##x, 0x8E);

void initIRQ()
{
	//Remap the IRQ.
	remapIRQ();

	mapIRQtoIDT(0);
	mapIRQtoIDT(1);
	mapIRQtoIDT(2);
	mapIRQtoIDT(3);
	mapIRQtoIDT(4);
	mapIRQtoIDT(5);
	mapIRQtoIDT(6);
	mapIRQtoIDT(7);
	mapIRQtoIDT(8);
	mapIRQtoIDT(9);
	mapIRQtoIDT(10);
	mapIRQtoIDT(11);
	mapIRQtoIDT(12);
	mapIRQtoIDT(13);
	mapIRQtoIDT(14);
	mapIRQtoIDT(15);
}

// IRQ handlers in kernel/irq.s point here.
void handleIRQ(FaultData* fd)
{
	//Pointer to the handler function.
	void (*handler)(FaultData*);

	//If we have a handler (it doesn't point to null), call it.
	handler = irq_routines[fd->interrupt - 32];
	if (handler != 0)
	{
		handler(fd);
	}

	//Interrupt request 8-15 are slave PIC interupts --
	//send an EOI (0x20) to them.
	if (fd->interrupt - 32 >= 8)
	{
		outbyte(PIC2, PIC_EOI);
	}

	//Call the end of interrupt to the MASTER PIC.
	outbyte(PIC1, PIC_EOI);
}