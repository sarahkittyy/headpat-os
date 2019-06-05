#pragma once

#include "std/common.h"
#include "std/math.h"

/**
 * @brief Sets a block of memory of bytes `num` to `value.
 * 
 * @param block The block of memory. 
 * @param value The new value of each byte in that memory.
 * @param num The number of bytes to set.
 * @return void* The set bytes.
 */
void* memset(void* block, uint32_t value, size_t num);