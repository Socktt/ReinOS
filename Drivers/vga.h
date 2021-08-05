#ifndef VGA_H
#define VGA_H
#define VIDEO_MEM (char *)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 50
#define ROW_COLOR 0x1F
void print(const char* text);
void setCursorPosRaw(uint16_t pos);
void setCursorPos(int x, int y);
void disableCursor();
uint16_t getCursorPosition(void);
void enableCursor(uint8_t cursor_start, uint8_t cursor_end);
void clearScreen();
void colourScreen(uint8_t colour);
void topRow();
void bottomRow();
void resetScreen();
void drawPixel(uint8_t x, uint8_t y, uint8_t colour);
void graphicsClearScreen(uint8_t colour);
void drawPalette(uint8_t x, uint8_t y);
#endif