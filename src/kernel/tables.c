#include "kernel/tables.h"

void initTables()
{
	initGDT();
	initIDT();
	initISRS();
	initIRQ();
}