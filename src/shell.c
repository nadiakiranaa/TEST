#include "shell.h"
#include "kernel.h"
#include "std_lib.h"
extern int text_color;
extern void setTextColor(int color);

void clearScreen() {
    int i;
    for (i = 0; i < 25 * 80; i++) {
        putInMemory(0xB800, i * 2, ' ');
        putInMemory(0xB800, i * 2 + 1, text_color);
    }
}

void printRandomYogurtResponse() {
    char *responses[3];
    int count = 3;
    int i = 0;
    unsigned int tick;
    int index;

    responses[0] = "yo";
    responses[1] = "ts unami gng </3";
    responses[2] = "sygau";

    tick = getBiosTick();
    index = mod(tick ^ 0xA5, count);

    printString("gurt> ");
    printString(responses[index]);
    printString("\r\n");
}

void handleGrandCompany(char *company, char *username) {
    if (strcmp(company, "maelstrom") == 0) {
        setTextColor(0x0C);  // merah terang
        clearScreen();
        strcpy(username, "user@Storm");
    } else if (strcmp(company, "twinadder") == 0) {
        setTextColor(0x0E);  // kuning terang
        clearScreen();
        strcpy(username, "user@Serpent");
    } else if (strcmp(company, "immortalflames") == 0) {
        setTextColor(0x09);  // biru muda
        clearScreen();
        strcpy(username, "user@Flame");
    } else if (strcmp(company, "clear") == 0 || company[0] == '\0') {
        setTextColor(0x07);  // warna default abu-putih
        clearScreen();
        strcpy(username, "user");
        printString("You are now neutral. The Grand Companies are sad.\n");
    } else {
        printString("Error: Unknown Grand Company\n");
    }
}

void shell() {
    char buf[128];
    char cmd[64];
    char arg[2][64];
    char username[64];
    char resultStr[16];
    int a, b, result;

    strcpy(username, "user");

    printString("Welcome to EorzeOS!\n");

    while (true) {
        printString(username);
        printString("> ");

        readString(buf);
        parseCommand(buf, cmd, arg);

        if (strcmp(cmd, "yo") == 0) {
            printString("gurt\n");
        } else if (strcmp(cmd, "gurt") == 0) {
            printString("yo\n");
        } else if (strcmp(cmd, "user") == 0) {
            if (arg[0][0] != '\0') {
                strcpy(username, arg[0]);
                printString("Username changed to ");
                printString(username);
                printString("\n");
            } else {
                strcpy(username, "user");
                printString("Username changed to user\n");
            }
        } else if (strcmp(cmd, "add") == 0 || strcmp(cmd, "sub") == 0 || strcmp(cmd, "mul") == 0 || strcmp(cmd, "div") == 0) {
            atoi(arg[0], &a);
            atoi(arg[1], &b);

            if (strcmp(cmd, "add") == 0) {
                result = a + b;
            } else if (strcmp(cmd, "sub") == 0) {
                result = a - b;
            } else if (strcmp(cmd, "mul") == 0) {
                result = a * b;
            } else {
                if (b == 0) {
                    printString("Error: Division by zero\n");
                    continue;
                }
                result = div(a, b);
            }

            itoa(result, resultStr);
            printString(resultStr);
            printString("\n");
        } else if (strcmp(cmd, "grandcompany") == 0) {
            handleGrandCompany(arg[0], username);
        } else if (strcmp(cmd, "clear") == 0) {
            clearScreen();
            setTextColor(0x07);
            strcpy(username, "user");
        } else if (strcmp(cmd, "yogurt") == 0) {
            printRandomYogurtResponse();
        } else {
            printString(buf);
            printString("\n");
        }
    }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
    int i = 0, j = 0, k = 0;

    clear((byte *)cmd, 64);
    clear((byte *)arg[0], 64);
    clear((byte *)arg[1], 64);

    while (buf[i] != ' ' && buf[i] != '\0') {
        cmd[i] = buf[i];
        i++;
    }
    cmd[i] = '\0';

    if (buf[i] == ' ') i++;

    while (buf[i] != ' ' && buf[i] != '\0') {
        arg[0][j++] = buf[i++];
    }
    arg[0][j] = '\0';

    if (buf[i] == ' ') i++;

    while (buf[i] != '\0') {
        arg[1][k++] = buf[i++];
    }
    arg[1][k] = '\0';
}
