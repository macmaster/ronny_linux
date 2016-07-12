/** kernel.c *******************************
 *
 * kernel routines for my operating sys.
 * uses a VGA text buffer at addr 0xb8000
 *
 * Author: Ronald Macmaster
 * Date: 07/12/16
 *
 ******************************************/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum vga_color {
	BLACK = 0x00,
	BLUE = 0x01,
	GREEN = 0x02,
	CYAN = 0x03,
	RED = 0x04,
	MAGENTA = 0x05,
	BROWN = 0x06,
	LIGHT_GREY = 0x07,
	DARK_GREY = 0x08,
	LIGHT_BLUE = 0x09,
	LIGHT_GREEN = 0x0A,
	LIGHT_CYAN = 0x0B,
	LIGHT_RED = 0x0C,
	LIGHT_MAGENTA = 0x0D,
	LIGHT_BROWN = 0x0E,
	WHITE = 0x0F,
};

/* generator and utility functions */

uint8_t VGAColor(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint16_t VGAChar(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

size_t strlen(const char *str) {
	size_t len = 0;
	while(str[len] != '\0') {len += 1;}
	return len;
}

/* VGA and terminal constants */

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

/* terminal procedures */

void terminal_init() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = VGAColor(LIGHT_GREY, BLACK);
	terminal_buffer = (uint16_t *) 0xB8000;

	/* clear terminal */
	for(size_t y = 0; y < VGA_HEIGHT; y++) {
		for(size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = VGAChar(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = VGAChar(c, color);
}

void terminal_putchar(char c) {
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	terminal_column = (terminal_column + 1) % VGA_WIDTH;
	if(terminal_column == 0) {
		terminal_row = (terminal_row + 1) % VGA_HEIGHT;
	}
}

void terminal_putstr(const char *data) {
	size_t index = 0;
	while(data[index] != '\0') {
		terminal_putchar(data[index++]);
	}
}

/** kernel_main() **/

void kernel_main() {
	terminal_initialize();
	terminal_putstr("Welcome to ronny linux!\n");
}
