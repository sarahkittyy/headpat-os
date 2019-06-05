#include "std/io.h"
#include "std/serial.h"

int kmain()
{
	//Initialization.
	initSerial();
	screenClear();

	screenWrite("*pats~<3*");

	comWrite(COM1, "Hello from com1!");

	return 0;
}