#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#include "../stuff/typeDef.h"
#include "../stuff/Misc.h"
#include "./port_io.h"
#include "./vga.h"

char kbd_US [128] =
        {
                0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
                '\t', /* <-- Tab */
                'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
                0, /* <-- control key */
                'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
                '*',
                0,  /* Alt */
                ' ',  /* Space bar */
                0,  /* Caps lock */
                0,  /* 59 - F1 key ... > */
                0,   0,   0,   0,   0,   0,   0,   0,
                0,  /* < ... F10 */
                0,  /* 69 - Num lock*/
                0,  /* Scroll Lock */
                0,  /* Home key */
                0,  /* Up Arrow */
                0,  /* Page Up */
                '-',
                0,  /* Left Arrow */
                0,
                0,  /* Right Arrow */
                '+',
                0,  /* 79 - End key*/
                0,  /* Down Arrow */
                0,  /* Page Down */
                0,  /* Insert Key */
                0,  /* Delete Key */
                0,   0,   0,
                0,  /* F11 Key */
                0,  /* F12 Key */
                0,  /* All other keys are undefined */
        };

const char Days[7][11] = {"Sunday\n", "Monday\n", "Tuesday\n", "Wednesday\n", "Thursday\n", "Friday\n", "Saturday\n"};

void keyLoop() {
    char *keyboardMemLoc = (char *)VIDEO_MEM + VGA_WIDTH * (VGA_HEIGHT - 2);
    uint8_t lastKey = inb(0x60);
    char buffer[256];
    uint8_t bufferIndex = 0;
    for(;;){
        uint8_t c = inb(0x60);
        if(c!=lastKey){
            char letter = kbd_US[int(c)];
            if(letter!=0) {
                if(letter=='\n' && kbd_US[int(lastKey)]!='\n'){
                    print(buffer);
                    print("\n");
                    uint16_t pos = getCursorPosition();
                    uint8_t y = pos / VGA_WIDTH;

                    if(y >= 24)
                        resetScreen();
                    //---------------------------
                    // Define Commands
                    //---------------------------
                    if(strcmp(buffer, "clear") == 0) {
                        resetScreen();
                    } else if(strcmp(buffer, "date") == 0) {
                        outb(0x70, (1 << 7) | (0x06));
                        char weekday = inb(0x71);
                        print(Days[weekday - 1]);
                    } else {
                        print("Unknown Command: ");
                        print(buffer);
                        print("\n");
                    }

                    lastKey = c;
                    keyboardMemLoc = (char *)VIDEO_MEM + VGA_WIDTH * (VGA_HEIGHT - 2);
                    bottomRow();
                    bufferIndex = 0;
                    for(int i=0; i<256;i++)
                        buffer[i] = 0;
                } else {
                    *keyboardMemLoc = letter;
                    buffer[bufferIndex] = letter;
                    bufferIndex++;
                    keyboardMemLoc += 2;
                    lastKey = c;
                }
            } else {
                lastKey = c;
            }
        }
    }
}
#pragma clang diagnostic pop