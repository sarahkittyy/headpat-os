#include "std/serial.h"

void initSerial()
{
	setBaudRate(COM1, 1);
	setBaudRate(COM2, 1);
	setBaudRate(COM3, 1);
	setBaudRate(COM4, 1);

	configureSerial(COM1);
	configureSerial(COM2);
	configureSerial(COM3);
	configureSerial(COM4);
}

void setBaudRate(uint32_t port, uint16_t divisor)
{
	//Enable DLAB
	outbyte(COM_LINE_CONTROL_PORT(port), COM_ENABLE_DLAB);

	//Send the low & high bytes of the divisor.
	outbyte(COM_DATA_PORT(port), divisor & 0xff);
	outbyte(COM_DATA_PORT(port), (divisor >> 8) & 0xff);

	//Disable DLAB
	outbyte(COM_LINE_CONTROL_PORT(port), 0);
}

void configureSerial(uint32_t port)
{
	//Configure the line
	outbyte(COM_LINE_CONTROL_PORT(port), 0x03);
	//Configure the FIFO queue.
	outbyte(COM_FIFO_CONTROL_PORT(port), 0b11000111);
	//Configure the modem to ready.
	outbyte(COM_MODEM_CONTROL_PORT(port), 0b0000011);
}

bool isSerialFIFOEmpty(uint32_t port)
{
	//Returns if the flag for the queue being empty
	//is set (bit 5) in the line status port.
	return inbyte(COM_LINE_STATUS_PORT(port)) & 0b100000;
}

void comSend(uint32_t port, char c)
{
	//Wait until the FIFO is empty.
	while (!isSerialFIFOEmpty(port))
	{
	}
	outbyte(COM_DATA_PORT(port), c);
}

void comWrite(uint32_t port, const char* str)
{
	//Send the string byte-by-byte.
	size_t len = strlen(str);
	for (size_t i = 0; i < len; ++i)
	{
		comSend(port, str[i]);
	}
}