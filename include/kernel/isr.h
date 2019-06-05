#pragma once

#include "kernel/idt.h"
#include "std/serial.h"

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