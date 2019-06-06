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

/**
 * @brief Converts a number to a digit.
 * 
 * @param number The number to convert
 * @return char That number's corresponding digit.
 */
char todigit(uint8_t number)
{
	static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (number > sizeof(digits))
	{
		return '-';
	}
	else
	{
		return digits[number];
	}
}

char* itoa(char* dest, int input, int base)
{
	//Special case for 0.
	if (input == 0)
	{
		dest[0] = '0';
		return dest;
	}

	int sign = input / abs(input);
	input	= abs(input);
	for (int i = 0; input != 0; ++i)
	{
		int d   = input % base;
		dest[i] = todigit(d);
		input /= base;
	}
	//Append a - if the sign is -
	if (sign == -1)
	{
		dest[strlen(dest)] = '-';
	}

	//Reverse the string.
	reverse(dest);
	return dest;
}

void reverse(char* in)
{
	size_t len = strlen(in);

	for (size_t i = 0; i < len / 2; ++i)
	{
		char t			= in[i];
		in[i]			= in[len - i - 1];
		in[len - i - 1] = t;
	}
}

void strncat(char* dest, const char* src, size_t n)
{
	size_t dest_start = strlen(dest);
	for (size_t i = 0; i < n; ++i)
	{
		dest[dest_start + i] = src[i];
	}
}

void strcat(char* dest, const char* src)
{
	//Just call strncat.
	strncat(dest, src, strlen(src));
}

void sprintf(char* dest, const char* fmt, ...)
{
	//Call vsprintf().
	va_list args;
	va_start(args, fmt);
	vsprintf(dest, fmt, args);
}

void vsprintf(char* dest, const char* fmt, va_list iargs)
{
	va_list args;
	va_copy(args, iargs);
	//Iterate over the fmt string.
	size_t len = strlen(fmt);
	int dest_i = 0;   //Dest vs Format index
	for (size_t fmt_i = 0; fmt_i < len; ++fmt_i)
	{
		char current = fmt[fmt_i];
		//If the current character is a % sign.
		if (current == '%')
		{
			//Get the next character.
			char type = fmt[fmt_i + 1];
			switch (type)
			{
			default:
				break;
			case '%':
				dest[dest_i] = '%';
				dest_i++;
				break;
			case 'i':
			{
				//Get the next va_arg as an integer.
				int arg = va_arg(args, int);
				//Concatenate it onto the result.
				char str[11] = {0};
				itoa(str, arg, 10);
				comWrite(COM1, str);
				strcat(dest, str);
				dest_i += strlen(str);
				break;
			}
			case 's':
			{
				const char* arg = va_arg(args, const char*);
				strcat(dest, arg);
				dest_i += strlen(arg);
				break;
			}
			case 'h':
			{
				//Get the next va_arg as an integer.
				int arg = va_arg(args, int);
				//Concatenate it onto the result.
				char str[11] = {0};
				itoa(str, arg, 16);
				comWrite(COM1, str);
				strcat(dest, str);
				dest_i += strlen(str);
				break;
			}
			case 'b':
			{
				//Get the next va_arg as an integer.
				int arg = va_arg(args, int);
				//Concatenate it onto the result.
				char str[11] = {0};
				itoa(str, arg, 2);
				comWrite(COM1, str);
				strcat(dest, str);
				dest_i += strlen(str);
				break;
			}
			}

			//Skip the next character.
			fmt_i++;
		}
		else
		{

			//Copy the character to the destination.
			dest[dest_i] = current;
			dest_i++;
		}
	}
}