#pragma once

#include "kernel/idt.h"
#include "std/serial.h"

#define _externISR(x) void _isr_##x()
_externISR(0);
_externISR(1);
_externISR(2);
_externISR(3);
_externISR(4);
_externISR(5);
_externISR(6);
_externISR(7);
_externISR(8);
_externISR(9);
_externISR(10);
_externISR(11);
_externISR(12);
_externISR(13);
_externISR(14);
_externISR(15);
_externISR(16);
_externISR(17);
_externISR(18);
_externISR(19);
_externISR(20);
_externISR(21);
_externISR(22);
_externISR(23);
_externISR(24);
_externISR(25);
_externISR(26);
_externISR(27);
_externISR(28);
_externISR(29);
_externISR(30);
_externISR(31);

/**
 * @brief Data representing the state of the system on an interrupt catch.
 * 
 */
typedef struct FaultData
{
	uint32_t gs, fs, es, ds;						   //Segments pushed last
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;   //From `pusha`
	uint32_t interrupt, err_code;
	uint32_t eip, cs, eflags, useresp, ss;   // Pushed by the processor automatically.

} __attribute__((packed)) FaultData;

/**
 * @brief Initialize the interrupt service routines.
 * 
 */
void initISRS();