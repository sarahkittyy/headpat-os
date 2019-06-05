#pragma once

#include "std/common.h"

/**
 * @brief Flush the initialized GDT.
 * 
 * @see kernel/gdt.s
 */
void flushGDT();

/**
 * @brief Initialises the GDT and GDTP and flushes it.
 * 
 */
void initGDT();

/**
 * @brief An entry in the GDT.
 * 
 */
typedef struct gdt_entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry;

/**
 * @brief Pointer information to the gdt.
 * Use with asm(lgdt)
 * 
 */
typedef struct gdt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_ptr;