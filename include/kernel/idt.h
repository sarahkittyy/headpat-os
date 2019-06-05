#pragma once

#include "std/common.h"
#include "std/io.h"
#include "std/lib.h"
#include "std/serial.h"

/**
 * @brief See kernel/idt.s, initializes the IDT.
 * 
 */
void initIDT();

/**
 * @brief Configure an IDT entry.
 * 
 * @param num The interrupt number.
 * @param base The address of the function to call.
 * @param flags The interrupt routine flags (usually 0b10001110)
 */
void setIDTEntry(size_t num,
				 /* selector = 0x08 */
				 uint32_t base,
				 uint8_t flags);

/**
 * @brief Flushes the idtp. Called by initIDT().
 * 
 * @see kernel/idt.s
 */
void flushIDT();

/**
 * @brief An entry in the IDT.
 * 
 */
typedef struct idt_entry
{
	uint16_t base_low;
	uint16_t selector;
	uint8_t reserved;
	/*
	 * | 7       | 6 5 | 4 3 2 1 0    |
	 * | Present | DPL | Always 01110 |
	 */
	uint8_t flags;
	uint16_t base_high;
} __attribute__((packed)) idt_entry;

/**
 * @brief The pointer to the IDT.
 * 
 */
typedef struct idt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_ptr;