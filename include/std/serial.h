#pragma once

#include "common.h"
#include "io.h"

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

#define COM_ENABLE_DLAB (0b10000000)

#define COM_DATA_PORT(com) (com)
#define COM_FIFO_CONTROL_PORT(com) (com + 2)
#define COM_LINE_CONTROL_PORT(com) (com + 3)
#define COM_MODEM_CONTROL_PORT(com) (com + 4)
#define COM_LINE_STATUS_PORT(com) (com + 5)

/**
 * @brief Initializes the four COM ports.
 * 
 */
void initSerial();

/**
 * @brief Configure the baud rate of a com port.
 * 
 * @param port The port to configure.
 * @param divisor The bits/s rate divisor.
 */
void setBaudRate(uint32_t port, uint16_t divisor);

/**
 * @brief Configures a COM port for use.
 * 
 * @param port The port to configure.
 */
void configureSerial(uint32_t port);

/**
 * @brief Checks if the COM FIFO port is empty.
 * 
 * @param port The port to check.
 * 
 * @returns true If the FIFO queue is empty.
 */
bool isSerialFIFOEmpty(uint32_t port);

/**
 * @brief Send a byte to the com port.
 * 
 * @param port The port to send the byte to.
 * @param c The character to send.
 */
void comSend(uint32_t port, char c);

/**
 * @brief Writes a string to the given com port.
 * 
 * @param port The port to send the byte to.
 * @param str The string to send.
 */
void comWrite(uint32_t port, const char* str);