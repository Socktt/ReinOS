#include "../stuff/typeDef.h"
#include "../Drivers/vga.h"
#include "../Drivers/port_io.h"

#define VIDEO_MEM (char *)0xb8000

extern "C" void main(){
    topRow();
    bottomRow();
    print("*CONFIDENTIAL SOCKTTSOFT* Rein OS\n");
    print("__________       .__         ________    _________\n");
    print("\\______   \\ ____ |__| ____   \\_____  \\  /   _____/\n");
    print(" |       _// __ \\|  |/    \\   /   |   \\ \\_____  \\ \n");
    print(" |    |   \\  ___/|  |   |  \\ /    |    \\/        \\\n");
    print(" |____|_  /\\___  >__|___|  / \\_______  /_______  /\n");
    print("        \\/     \\/        \\/          \\/        \\/ \n");
    print("Welcome to Rein OS!\n");
    print("|\\\n");
    print("| \\\n");
    print("|  \\\n");
    print("|___\\\n");
    print("wowzers what a cool shape!!!\n");
    return;
}
