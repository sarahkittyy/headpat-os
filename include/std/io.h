#pragma once

#include "common.h"
#include "std/string.h"

/**
 * @brief Convert a screen X/Y position to a screen absolute position.
 * 
 * @param x The character x position.
 * @param y The character y position.
 * @return int The absolute screen position equivalent.
 */
uint32_t position(uint32_t x, uint32_t y);

/**
 * @brief Get the X component from an absolute framebuffer position.
 * 
 * @param position The framebuffer position.
 * @return uint32_t The x position on the screen.
 */
uint32_t xComponent(uint32_t position);

/**
 * @brief Get the Y component from an absolute framebuffer position.
 * 
 * @param position The framebuffer pos.
 * @return uint32_t The y position on the screen.
 */
uint32_t yComponent(uint32_t position);


/**
 * @brief Get the color byte  associated with a text fg/bg color.
 * 
 * @param fg The text color.
 * @param bg The background color.
 * 
 * @returns the color byte
 */
uint8_t getColorByte(uint8_t fg, uint8_t bg);

/**
 * @brief Write a cell to the screen.
 * 
 * @param pos The character position.
 * @param c The character.
 * @param color The color bytee.
 */
void writeCell(uint32_t pos, char c, uint8_t color);

/**
 * @brief Puts the cursor at the given position.
 * 
 * @param pos The new cursor position.
 */
void setCursor(uint16_t pos);

/**
 * @brief Get the cursor position.
 * 
 * @return int The absolute fb position of the cursor.
 */
uint16_t getCursor();

/**
 * @brief Clears the framebuffer.
 * 
 */
void screenClear();

/**
 * @brief Output a string to the framebuffer.
 * 
 * @param str The string to send.
 */
void screenWrite(const char* str);

/**
 * @brief Write a byte out to an i/o port.
 * 
 * @param port The port.
 * @param byte The byte to send.
 */
void outbyte(uint32_t port, uint8_t byte);

/**
 * @brief Receive a byte on a port.
 * 
 * @param port The port to retrieve the byte from.
 * @return uint8_t The retrieved byte.
 */
uint8_t inbyte(uint32_t port);