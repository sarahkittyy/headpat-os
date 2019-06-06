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

	comWritef(COM1, "Hello, %s! Your number is %i!", "sawah", 42);

	return 0;
}