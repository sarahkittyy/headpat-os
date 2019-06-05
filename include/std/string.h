#pragma once

#include "std/common.h"
#include "std/math.h"

/**
 * @brief Get the length of a null-terminated string.
 * 
 * @param str The string
 * @return uint32_t The length.
 */
size_t strlen(const char* str);

/**
 * @brief Concatenate n bytes of src onto dest.
 * 
 * @param dest The destination string.
 * @param src The source string
 * @param n The amount of bytes
 */
void strncat(char* dest, const char* src, size_t n);

/**
 * @brief Concatenate a string onto another.
 * 
 * @param dest The destination string.
 * @param src The source string.
 */
void strcat(char* dest, const char* src);

/**
 * @brief Convert an integer to a string.
 * 
 * @param dest Where the string will be written to.
 * @param input The input integer.
 * @param base The base of the integer.
 * @return char* `dest`
 */
char* itoa(char* dest, int input, int base);

/**
 * @brief Reverse a string in-place.
 * 
 * @param in The string to reverse.
 */
void reverse(char* in);

/**
 * @brief Generates a formatted string according to `fmt` and the
 * following arguments, and puts it into `dest`.
 * 
 * @param dest The resulting string.
 * @param fmt The formatted string.
 * @param ... The arguments according to `fmt`
 */
void sprintf(char* dest, const char* fmt, ...);