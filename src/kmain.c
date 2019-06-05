#include "kernel/tables.h"
#include "std/io.h"
#include "std/serial.h"

int kmain()
{
	//Initialization.
	initTables();
	initSerial();
	screenClear();

	screenWrite("it rly do be like dat sometimes");

	asm("int $0xA");

	screenWrite("\nafter fault");

	return 0;
}