#include "shell.h"
#include "kernel.h"
#include "std_lib.h"
// extern int text_color;
// extern void setTextColor(int color);

int text_color = 0x07; // default color: white

void setTextColor(int color) {
    text_color = color;
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
    index = mod(getBiosTick(), count);
    
    printString("gurt> ");
    printString(responses[index]);
    printString("\r\n");
}

void handleGrandCompany(char *company, char *username, char *host) {
    int i = 0;

    if (strcmp(company, "maelstrom")) {
        setTextColor(0x0C);  // merah terang
        clearScreen(text_color);
        strcpy(host, "@Storm");
        printString("\r");
    } else if (strcmp(company, "twinadder")) {
        setTextColor(0x0E);  // kuning terang
        clearScreen(text_color);
        strcpy(host, "@Serpent");
    } else if (strcmp(company, "immortalflames")) {
        setTextColor(0x09);  // biru muda
        clearScreen(text_color);
        // Gunakan strcpy untuk mengganti host
        strcpy(host, "@Flame");
    
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
    char host[64]; // Default host
    int a, b, result;
    strcpy(host, "");
    strcpy(username, "user");
    interrupt(0x10, 0x0200, 0, 0, 0);
    printString("Welcome to EorzeOS!\n");
    printString("\r");
    while (true) {
        printString(username);
        printString(host);
        printString("> ");

        readString(buf);
        parseCommand(buf, cmd, arg);
        printString("\r");

        if (strcmp(cmd, "yo")) {
            printString("gurt\n");
            printString("\r");
        } else if (strcmp(cmd, "gurt")) {
            printString("yo\n");
            printString("\r");
        } else if (strcmp(cmd, "user")) {
            if (arg[0][0] != '\0') {
                strcpy(username, arg[0]);
                printString("Username changed to ");
                printString(username);
                printString("\n");
                printString("\r");
            } else {
                strcpy(username, "user");
                printString("Username changed to user\n");
                printString("\r");
            }
        } else if (strcmp(cmd, "add") || strcmp(cmd, "sub") || strcmp(cmd, "mul") || strcmp(cmd, "div")) {
            atoi(arg[0], &a);
            atoi(arg[1], &b);

            if (strcmp(cmd, "add")) {
                result = a + b;
            } else if (strcmp(cmd, "sub")) {
                result = a - b;
            } else if (strcmp(cmd, "mul")) {
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
            printString("\r");
        } else if (strcmp(cmd, "grandcompany")) {
            handleGrandCompany(arg[0], username, host);

        } else if (strcmp(cmd, "clear")) {
            setTextColor(0x07);  // warna default abu-putih
            clearScreen(text_color);
            strcpy(host, "");
            printString("\r");
        } else if (strcmp(cmd, "yogurt")) {
            printRandomYogurtResponse();
            printString("\r");
        } else {
            printString(buf);
            printString("\r");
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
