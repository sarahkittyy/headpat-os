#include "std/io.h"

uint32_t position(uint32_t x, uint32_t y)
{
	return (y * FB_COLUMNS + x);
}

uint32_t xComponent(uint32_t position)
{
	return position % FB_COLUMNS;
}

uint32_t yComponent(uint32_t position)
{
	return position / FB_COLUMNS;
}

uint8_t getColorByte(uint8_t fg, uint8_t bg)
{
	return ((bg & 0x0F) << 4) | (fg & 0x0F);
}

void writeCell(uint32_t pos, char c, uint8_t color)
{
	pos *= 2;

	/*
	 * bits 0-8 : color
	 * bits 9-15 : char
	 */
	char* fb	= (char*)FB_ADDR;
	fb[pos]		= c;
	fb[pos + 1] = color;
}

void setCursor(uint16_t pos)
{
	/*
	 * We're sending a 2 byte integer position, so
	 * we send the high byte first, then the low byte.
	 */
	outbyte(FB_CONFIG_PORT, FB_HIGHBYTE_NEXT);
	outbyte(FB_DATA_PORT, (pos & 0xff00) >> 8);
	//Low byte
	outbyte(FB_CONFIG_PORT, FB_LOWBYTE_NEXT);
	outbyte(FB_DATA_PORT, pos & 0xff);
}

uint16_t getCursor()
{
	//High byte
	outbyte(FB_CONFIG_PORT, FB_HIGHBYTE_NEXT);
	uint8_t high = inbyte(FB_DATA_PORT);
	//Low byte
	outbyte(FB_CONFIG_PORT, FB_LOWBYTE_NEXT);
	uint8_t low = inbyte(FB_DATA_PORT);

	return (high << 8) | low;
}

void screenClear()
{
	//Write an invisible charater to all cells on the screen.
	for (size_t x = 0; x < FB_COLUMNS; ++x)
	{
		for (size_t y = 0; y < FB_ROWS; ++y)
		{
			writeCell(position(x, y), ' ', getColorByte(BLACK, BLACK));
		}
	}
	setCursor(0);
}

void screenWrite(const char* str)
{
	size_t len			= strlen(str);
	uint16_t cursor_pos = getCursor();
	//Iterate over all characters.
	for (size_t i = 0; i < len; ++i)
	{
		char ch = str[i];
		if (ch == '\n')   //Move the cursor to the next line on a newline.
		{
			cursor_pos = position(0, yComponent(cursor_pos) + 1);
		}
		else
		{   //Write the character.
			writeCell(cursor_pos, ch, COLOR_DEFAULT);
			cursor_pos++;
		}
	}
	//Set the final cursor position.
	setCursor(cursor_pos);
}

void screenWritef(const char* fmt, ...)
{
	char str[1000] = {0};
	va_list args;
	va_start(args, fmt);
	vsprintf(str, fmt, args);
	screenWrite(str);
	va_end(args);
}