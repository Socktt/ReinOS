#include "../stuff/typeDef.h"
#include "../Drivers/vga.h"
#include "../Drivers/port_io.h"
#include "../Drivers/keyboard.h"

void printLogo();

extern "C" void main(){
    resetScreen();
    disableCursor();
    printLogo();
    print("Welcome to Rein OS!\n");
    keyLoop();
    return;
}

void printLogo(){
    print("__________       .__         ________    _________\n");
    print("\\______   \\ ____ |__| ____   \\_____  \\  /   _____/\n");
    print(" |       _// __ \\|  |/    \\   /   |   \\ \\_____  \\ \n");
    print(" |    |   \\  ___/|  |   |  \\ /    |    \\/        \\\n");
    print(" |____|_  /\\___  >__|___|  / \\_______  /_______  /\n");
    print("        \\/     \\/        \\/          \\/        \\/ \n");
}