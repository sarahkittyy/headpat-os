#pragma once

#define FB_ADDR 0x000B8000
#define FB_ROWS 24
#define FB_COLUMNS 80

#define FB_CONFIG_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
#define FB_HIGHBYTE_NEXT 14
#define FB_LOWBYTE_NEXT 15

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef uint32_t size_t;

typedef uint8_t bool;
#define true 1
#define false 0

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LGREY 7
#define GREY 8
#define LBLUE 9
#define LGREEN 10
#define LCYAN 11
#define LRED 12
#define LMAGENTA 13
#define LBROWN 14
#define WHITE 15
#define COLOR_DEFAULT (LGREY & 0xff)