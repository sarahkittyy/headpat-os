#pragma once

#include "kernel/gdt.h"
#include "kernel/idt.h"
#include "kernel/isr.h"

/**
 * @brief Init the GDT and IDT.
 * 
 */
void initTables();