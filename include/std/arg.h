#pragma once

typedef char* va_list;
#define va_start(args, fmt) args = (char*)(&args) + sizeof(&args)
#define va_arg(args, type) \
	*((type*)args);        \
	args += sizeof(type)
#define va_end(args) args = NULL