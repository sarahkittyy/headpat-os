#include "kernel/isr.h"

//Load the external interrupt service routine procedures
#define externISR(x) extern void _isr_##x()
externISR(0);
externISR(1);
externISR(2);
externISR(3);
externISR(4);
externISR(5);
externISR(6);
externISR(7);
externISR(8);
externISR(9);
externISR(10);
externISR(11);
externISR(12);
externISR(13);
externISR(14);
externISR(15);
externISR(16);
externISR(17);
externISR(18);
externISR(19);
externISR(20);
externISR(21);
externISR(22);
externISR(23);
externISR(24);
externISR(25);
externISR(26);
externISR(27);
externISR(28);
externISR(29);
externISR(30);
externISR(31);

//
#define setIDTEntryNum(x) setIDTEntry(x, (uint32_t)_isr_##x, 0b10001110)

void initISRS()
{
	/*
	 * Initializs all Interrupt descriptor table entries with pointers to the asm interrupt labels,
	 * which push cpu data and call the generic fault handler.
	 */
	setIDTEntryNum(0);
	setIDTEntryNum(1);
	setIDTEntryNum(2);
	setIDTEntryNum(3);
	setIDTEntryNum(4);
	setIDTEntryNum(5);
	setIDTEntryNum(6);
	setIDTEntryNum(7);
	setIDTEntryNum(8);
	setIDTEntryNum(9);
	setIDTEntryNum(10);
	setIDTEntryNum(11);
	setIDTEntryNum(12);
	setIDTEntryNum(13);
	setIDTEntryNum(14);
	setIDTEntryNum(15);
	setIDTEntryNum(16);
	setIDTEntryNum(17);
	setIDTEntryNum(18);
	setIDTEntryNum(19);
	setIDTEntryNum(20);
	setIDTEntryNum(21);
	setIDTEntryNum(22);
	setIDTEntryNum(23);
	setIDTEntryNum(24);
	setIDTEntryNum(25);
	setIDTEntryNum(26);
	setIDTEntryNum(27);
	setIDTEntryNum(28);
	setIDTEntryNum(29);
	setIDTEntryNum(30);
	setIDTEntryNum(31);
}

const char* exceptions[] = {
	"Divide by Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"};

/**
 * @brief The generic fault handler, called by all generic isrs.
 * 
 * @param fd The fault data. 
 */
void handleFault(FaultData* fd)
{
	//Inform of an exception.
	screenWritef("An exception occured: %s.\n", exceptions[fd->interrupt]);
	screenWritef("Detailed logging in COM4 output.");

	//Write info to COM4
	comWritef(COM4, "Exception: %s -- Interrupt #%i, Error Code #%i\n",
			  exceptions[fd->interrupt],
			  fd->interrupt,
			  fd->err_code);
	comWritef(COM4, "EAX = %h, EBX = %h, ECX = %h, EDX = %h\n",
			  fd->eax,
			  fd->ebx,
			  fd->ecx,
			  fd->edx);
	comWritef(COM4, "EDI = %h, ESI = %h, EBP = %h, ESP = %h\n",
			  fd->edi,
			  fd->esi,
			  fd->ebp,
			  fd->esp);
	comWritef(COM4, "GS = %h, FS = %h, ES = %h, DS = %h\n",
			  fd->gs,
			  fd->fs,
			  fd->es,
			  fd->ds);
	comWritef(COM4, "EIP = %h, CS = %h, EFlags = %b, UserESP = %h, SS = %h\n",
			  fd->eip,
			  fd->cs,
			  fd->eflags,
			  fd->useresp,
			  fd->ss);


	//Halt the system
	for (;;)
		;
}