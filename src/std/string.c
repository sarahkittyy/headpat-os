#include "std/string.h"

size_t strlen(const char* str)
{
	//simple strlen implementation
	size_t size = 0;
	while (*str++ != '\0')
	{
		size++;
	}
	return size;
}