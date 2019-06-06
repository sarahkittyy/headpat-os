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

	return 0;
}