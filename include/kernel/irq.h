#pragma once

#include "kernel/idt.h"
#include "kernel/isr.h"
#include "std/common.h"
#include "std/io.h"

#define PIC_EOI 0x20

#define PIC1 0x20
#define PIC2 0xA0

/**
 * @brief Initialize the IRQs.
 * 
 */
void initIRQ();

/**
 * @brief Configure a given interrupt request to be handled by the given function.
 * 
 * @param number The IRQ to handle. 
 * @param handler Function pointer to the handler.
 */
void installIRQ(size_t number, void (*handler)(FaultData*));

/**
 * @brief Unset a handler to an IRQ.
 * 
 * @param number The handler to null and ignore.
 */
void removeIRQ(size_t number);