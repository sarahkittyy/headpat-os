#include "kernel/gdt.h"
#include "std/io.h"
#include "std/serial.h"

int kmain()
{
	//Initialization.
	initTables();
	initSerial();
	screenClear();

	screenWrite("it rly do be like dat sometimes");

	comWrite(COM1, "Hello from com1!");

	return 0;
}