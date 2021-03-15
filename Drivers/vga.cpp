#include "../stuff/typeDef.h"
#include "./port_io.h"

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

void blueScreen(){
    for(int i = 0; i<VGA_HEIGHT;i++){
        for(int j = 0;j<VGA_WIDTH;j++){
            *(VIDEO_MEM + (i * VGA_HEIGHT * 2) + j * 2) = (const char)' ';
            *(VIDEO_MEM + (i * VGA_HEIGHT * 2) + j * 2 - 1) = (const char)0x1f;
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