#include "std_lib.h"

// Fungsi pembagian a / b, dengan angka negatif
int div(int a, int b) {
    int sign = 1;
    int result = 0;
    unsigned int ua, ub;

    if (b == 0) return 0; // hindari div by zero

    if (a < 0) {
        sign = -sign;
        ua = (unsigned int)(-a);
    } else {
        ua = (unsigned int)a;
    }

    if (b < 0) {
        sign = -sign;
        ub = (unsigned int)(-b);
    } else {
        ub = (unsigned int)b;
    }

    while (ua >= ub) {
        ua = ua - ub;
        result++;
    }

    return sign * result;
}

// Fungsi modulus a % b tanpa operator %
int mod(int a, int b) {
    int sign = 1;
    unsigned int ua, ub;

    if (b == 0) return 0; // hindari mod by zero

    if (a < 0) {
        sign = -1;
        ua = (unsigned int)(-a);
    } else {
        ua = (unsigned int)a;
    }

    if (b < 0) {
        ub = (unsigned int)(-b);
    } else {
        ub = (unsigned int)b;
    }

    while (ua >= ub) {
        ua = ua - ub;
    }

    return sign * (int)ua;
}

// strcmp sama seperti sebelumnya
bool strcmp(char *str1, char *str2) {
    int i;

    for (i = 0; ; i++) {
        if (str1[i] != str2[i]) return false;
        if (str1[i] == '\0') break;
    }
    return true;
}

void strcpy(char *dst, char *src) {
    int i;
    for (i = 0; ; i++) {
        dst[i] = src[i];
        if (src[i] == '\0') break;
    }
}

void clear(byte *buf, unsigned int size) {
    unsigned int i;
    for (i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

void atoi(char *str, int *num) {
    int i = 0;
    int sign = 1;
    int result = 0;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    *num = sign * result;
}

// itoa tanpa operator %
void itoa(int num, char *str) {
    int i = 0;
    int isNegative = 0;
    char temp[16];
    int j;
    int n;
    int count;

    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    while (num > 0) {
        n = num;
        // Cari digit terakhir tanpa operator %
        while (n >= 10) {
            n = n - 10;
        }
        temp[i] = '0' + n;
        i++;

        // Hitung num / 10 tanpa operator /
        count = 0;
        while (num >= 10) {
            num = num - 10;
            count++;
        }
        num = count;
    }

    if (isNegative) {
        temp[i] = '-';
        i++;
    }

    // Balik string hasil di temp ke str
    for (j = 0; j < i; j++) {
        str[j] = temp[i - j - 1];
    }
    str[i] = '\0';
}
