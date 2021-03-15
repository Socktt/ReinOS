#ifndef VGA_H
#define VGA_H
void print(const char* text);
void setCursorPosRaw(uint16_t pos);
void setCursorPos(int x, int y);
void clearScreen();
void blueScreen();
void topRow();
void bottomRow();
#endif