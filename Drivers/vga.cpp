#include "../stuff/typeDef.h"
#include "./port_io.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#define VIDEO_MEM (char *)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 50
#define ROW_COLOR 0x1F

uint16_t CursorPos = 0;

void setCursorPosRaw(uint16_t pos) {
    if(pos >= 0 && pos < 2000) {
		outb(0x3d4, 0x0f);
		outb(0x3d5, (uint8_t)(pos & 0xff));
		outb(0x3d4, 0x0e);
		outb(0x3d5, (uint8_t)((pos >> 8) & 0xff));
		CursorPos = pos;
	}
	return;
}

void setCursorPos(int x, int y) {
    uint16_t pos;
    pos = y * VGA_WIDTH + x;
    setCursorPosRaw(pos);
}

void disableCursor() {     // https://wiki.osdev.org/Text_Mode_Cursor
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void enableCursor(uint8_t cursor_start, uint8_t cursor_end) {      // https://wiki.osdev.org/Text_Mode_Cursor
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

uint16_t getCursorPosition(void) {      // https://wiki.osdev.org/Text_Mode_Cursor
    uint16_t pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;
    return pos;
}

void clearScreen(){
    for(int i = 0; i<VGA_HEIGHT;i++){
        for(int j = 0;j<VGA_WIDTH;j++){
            *(VIDEO_MEM + (i * VGA_HEIGHT * 2) + j * 2) = (const char)' ';
            *(VIDEO_MEM + (i * VGA_HEIGHT * 2) + j * 2 - 1) = (const char)0x0f;
        }
    }
    setCursorPos(0, 0);
    return;
}

void colourScreen(uint8_t colour){
    for(int i = 0; i<VGA_HEIGHT;i++){
        for(int j = 0;j<VGA_WIDTH;j++){
            *(VIDEO_MEM + (i * VGA_HEIGHT * 2) + j * 2) = (const char)' ';
            *(VIDEO_MEM + (i * VGA_HEIGHT * 2) + j * 2 - 1) = (const char)colour;
        }
    }
    setCursorPos(0, 0);
    return;
}

void topRow(){
    for(int i = 0;i<=VGA_WIDTH;i++){
        *(VIDEO_MEM + (i * 2)) = (const char)' ';
        *(VIDEO_MEM + (i * 2) - 1) = (const char)ROW_COLOR;
    }
    return;
}

void bottomRow(){
    for(int i = 0;i<=VGA_WIDTH;i++){
        *(VIDEO_MEM + (VGA_WIDTH * (VGA_HEIGHT - 2) + i * 2)) = (const char)' ';
        *(VIDEO_MEM + (VGA_WIDTH * (VGA_HEIGHT - 2) + i * 2) + 1) = (const char)ROW_COLOR;
    }
    return;
}

void print(const char* text) {
    uint8_t* textptr = (uint8_t*)text;
    uint16_t i = CursorPos;
    while(*textptr!=0){
        switch(*textptr){
            case 10:
                if(CursorPos < 1920){
                    i += VGA_WIDTH - i % VGA_WIDTH;
                }
                break;

            case 13:
                i -= i % VGA_WIDTH;
			    break;
            default:
                *(VIDEO_MEM + i * 2) = *textptr;
                i++;
        }
        textptr++;
    }
    setCursorPosRaw(i);
    return;
}

void resetScreen(){
    clearScreen();
    topRow();
    print("ReinOS Alpha");
    bottomRow();
    setCursorPos(0, 1);
    return;
}

void drawPixel(uint8_t x, uint8_t y, uint8_t colour){
    uint8_t * pos = (y * 320 + x) + (uint8_t *)0xA0000;
    *pos = colour;
    return;
}

void graphicsClearScreen(uint8_t colour){
    uint8_t * graphicsVideoMem = (uint8_t *)0xA0000;
    for(int i = 0;i < 200;i++){
        for(int j = 0;j < 320;j++){
            *graphicsVideoMem = colour;
            graphicsVideoMem++;
        }
    }
}

void drawPalette(uint8_t x, uint8_t y){
    uint8_t * graphicsVideoMem = (uint8_t *)0xA0000 + (y * 320 + x);
    uint8_t colourIndex = 0x0;
    for(uint8_t i = 0;i < 0xf;i++){
        for(uint8_t j = 0;j < 0xf;j++) {
            *graphicsVideoMem = colourIndex;
            colourIndex++;
            graphicsVideoMem++;
        }
        graphicsVideoMem += (320 - 0xf);
    }

}
#pragma clang diagnostic pop