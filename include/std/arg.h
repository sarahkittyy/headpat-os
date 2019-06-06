#pragma once

typedef char* va_list;
#define va_start(args, start) args = (char*)(&start) + sizeof(start)
#define va_arg(args, type) \
	*((type*)(args));      \
	args += sizeof(type)

#define va_copy(dest, src) ((void)(dest = src))
#define va_end(args) args = NULL