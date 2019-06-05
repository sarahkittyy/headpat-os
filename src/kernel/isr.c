#include "kernel/isr.h"

#define setIDTEntryNum(x) setIDTEntry(x, (uint32_t)_isr_##x, 0b10001110)

void initISRS()
{
	setIDTEntryNum(0);
	setIDTEntryNum(1);
	setIDTEntryNum(2);
	setIDTEntryNum(3);
	setIDTEntryNum(4);
	setIDTEntryNum(5);
	setIDTEntryNum(6);
	setIDTEntryNum(7);
	setIDTEntryNum(8);
	setIDTEntryNum(9);
	setIDTEntryNum(10);
	setIDTEntryNum(11);
	setIDTEntryNum(12);
	setIDTEntryNum(13);
	setIDTEntryNum(14);
	setIDTEntryNum(15);
	setIDTEntryNum(16);
	setIDTEntryNum(17);
	setIDTEntryNum(18);
	setIDTEntryNum(19);
	setIDTEntryNum(20);
	setIDTEntryNum(21);
	setIDTEntryNum(22);
	setIDTEntryNum(23);
	setIDTEntryNum(24);
	setIDTEntryNum(25);
	setIDTEntryNum(26);
	setIDTEntryNum(27);
	setIDTEntryNum(28);
	setIDTEntryNum(29);
	setIDTEntryNum(30);
	setIDTEntryNum(31);
}

void handleFault(struct FaultData* fd)
{
	comWrite(COM1, "FAULT HANDLED");
}