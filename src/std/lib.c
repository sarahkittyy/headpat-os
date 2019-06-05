#include "std/lib.h"

void* memset(void* block, uint32_t value, size_t num)
{
	//For every byte...
	for (size_t i = 0; i < num; ++i)
	{
		//Set the byte
		((uint8_t*)block)[i] = (uint8_t)value;
	}
	//Return the set memory.
	return block;
}