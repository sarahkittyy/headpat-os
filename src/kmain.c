#include "kernel/tables.h"
#include "std/io.h"
#include "std/lib.h"
#include "std/serial.h"

int kmain()
{
	//Initialization.
	initTables();
	initSerial();
	screenClear();

	int x = -503;
	char str[100];
	sprintf(str, "Hello, %s! Your number is %i.", "sawah", 5);
	screenWrite(str);

	return 0;
}