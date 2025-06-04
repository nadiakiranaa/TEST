#include "shell.h"
#include "kernel.h"

// int text_color = 0x07;



int main() {
    clearScreen(0x07);
    shell();
    return 0;
}

void printString(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        interrupt(0x10, 0x0E00 + str[i], 0, 0, 0);
        i++;
    }
}

void readString(char *buf) {
    int i = 0;
    char c;
    while (1) {
        c = interrupt(0x16, 0, 0, 0, 0); // BIOS keyboard input
        if (c == 13) { // Enter
            buf[i] = '\0';
            printString("\n");
            return;
        } else if (c == 8) { // Backspace
            if (i > 0) {
                i--;
                printString("\b \b");
            }
        } else {
            buf[i++] = c;
            interrupt(0x10, 0x0E00 + c, 0, 0, 0);
        }
    }
}


void clearScreen(int color) {
    int i;
    for (i = 0; i < 25 * 80; i++) {
        putInMemory(0xB800, i * 2, ' ');
        putInMemory(0xB800, i * 2 + 1, color);
    } 
     interrupt(0x10, 0x0200, 0, 0, 0);
}


