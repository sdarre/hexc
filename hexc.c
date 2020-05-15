#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>


void BinToDec(char * input);
void BinToHex(char * input);
void DecToBin(char * input);
void DecToHex(char * input);
void HexToBin(char * input);
void HexToDec(char * input);
void PrintHelp();


int main (int argc, char *argv[]) {

    if (argc <= 1) {
        PrintHelp();
        return 0;
    }
    char * conv = argv[1];

    void (*conversion)(char*);

    if (!strncmp(conv, "-bd", 4)) { conversion = BinToDec; }
    else if (!strncmp(conv, "-bh", 4)) { conversion = BinToHex; }
    else if (!strncmp(conv, "-db", 4)) { conversion = DecToBin; }
    else if (!strncmp(conv, "-dh", 4)) { conversion = DecToHex; }
    else if (!strncmp(conv, "-hb", 4)) { conversion = HexToBin; }
    else if (!strncmp(conv, "-hd", 4)) { conversion = HexToDec; }
    else {
        if (strncmp(conv, "-h", 2) || strncmp(conv, "--help", 6)) { 
            printf("Invalid argument.\n");
        }
        PrintHelp(); 
        return 0;
    }

    for (int i = 2; i < argc; i++) {
       conversion(argv[i]);
    }

    return 0;
}


void BinToDec(char * input) {
    unsigned long result = 0;
    int power = 0, valid = 1;
    printf("%s -> ", input);
    for (int i = strlen(input) - 1; i >= 0; i--) {
        if (power > 52) {
            printf("Binary value too large.\n");
            valid--;
            break;
        }
        if ((input[i] - '0') == 1) {
            result += pow(2, power);
        }
        else if ((input[i] - '0') != 0) {
            printf("Input not in binary form.\n");
            valid--;
            break;
        }
        power++;        
    }
    if (valid) printf("%lu\n", result);
    result = 0;
}


void BinToHex(char * input) {
    int power = 0, byte = 0, counter = 0;
    char * str = (char *) malloc(sizeof(char) * strlen(input));
    if (!str) {
        printf("Memory error.\n");
        exit(0);
    }
    printf("%s -> ", input);
    for (int i = strlen(input) - 1; i >= 0; i--) {
        if ((input[i] - '0') == 1) {
            byte += pow(2, power);
        }
        else if ((input[i] - '0') != 0) {
            printf("Input not in binary form.");
            break;
        }
        power++;
        if (power == 4 || i == 0) {
            if (byte > 9) { 
                byte += ('A' - 10); 
            }
            else { 
                byte += '0'; 
            }
            if (!(byte == '0' && i == 0)) {
                str[counter++] = (char) byte;
            }
            power = 0;
            byte = 0;
        }
    }
    for (int i = strlen(str); i >= 0; i--) {
        printf("%c", str[i]);
    }
    printf("\n");
    free(str);
    str = NULL;
}


void DecToBin(char * input) {
    int vector[64];
    char * ptr;
    unsigned long num = strtoul(input, &ptr, 10);
    if (errno == ERANGE) {
        printf("%s -> Decimal value too large.\n", input);
        errno = 0;
        return;
    }
    printf("%lu -> ", num);
    if (num == 0) {
        printf("0\n");
        return;
    }
    int n = 0;
    while (num > 0) {
        vector[n] = num % 2;
        num = num / 2;
        n++;
    }
    for (int i = n - 1; i >= 0; i--) {
        printf("%d", vector[i]);
    }
    printf("\n");
}


void DecToHex(char * input) {
    char * ptr;
    unsigned long num = strtoul(input, &ptr, 10);
    if (errno == ERANGE) {
        printf("%s -> Decimal value too large.\n", input);
        errno = 0;
        return;
    }
    printf("%s -> %lX\n", input, num);
}


void HexToBin(char * input) {
    int valid = 1;
    printf("%s -> ", input);
    for (int i = 0; i < strlen(input); i++) {
        if (!(input[i] > ('0' - 1) && input[i] < ('9' + 1)) 
            && !(input[i] > ('A' - 1) && input[i] < 'G') 
            && !(input[i] > ('a' - 1) && input[i] < 'g')) {
            printf("Input not in hexadecimal form.");
            valid--;
            break;
        }
    }
    for (int i = 0; i < strlen(input) && valid; i++) {
        switch(input[i]){
            case '0': printf("0000"); break;
            case '1': printf("0001"); break;
            case '2': printf("0010"); break;
            case '3': printf("0011"); break;
            case '4': printf("0100"); break;
            case '5': printf("0101"); break;
            case '6': printf("0110"); break;
            case '7': printf("0111"); break;
            case '8': printf("1000"); break;
            case '9': printf("1001"); break;
            case 'a':
            case 'A': printf("1010"); break;
            case 'b':
            case 'B': printf("1011"); break;
            case 'c':
            case 'C': printf("1100"); break;
            case 'd':
            case 'D': printf("1101"); break;
            case 'e':
            case 'E': printf("1110"); break;
            case 'f':
            case 'F': printf("1111"); break;
        }
    }
    printf("\n");
}


void HexToDec(char * input) {
    unsigned long result = 0;
    int power = 0, valid = 1;
    if (strlen(input) > 13) {
        printf("%s -> Hexadecimal value too large.\n", input);
        return;
    }
    for (int i = (strlen(input) - 1); i >= 0; i--) {
        if (input[i] > ('0' - 1) && input[i] < ('9' + 1)) {
            result += (input[i] - '0') * pow(16, power++);
        }
        else if (input[i] > ('A' - 1) && input[i] < 'G') {
            result += (input[i] - ('A' - 10)) * pow(16, power++);
        }
        else if (input[i] > ('a' - 1) && input[i] < 'g') {
            result += (input[i] - ('a' - 10)) * pow(16, power++);
        }
        else {
            printf("%s -> Input not in hexadecimal form.\n", input);
            valid--;
            break;
        }
    }
    if (valid) printf("%s -> %lu\n", input, result);
}


void PrintHelp() {
    printf("Run \"hexc {operator} {string1 string2 string3...}\" to produce a converted string or series of strings.\n");
    printf("The operators are as follows:\n\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("| Operator |      Description       |                  Limit (per string)                   |\n");
    printf("| ---------|------------------------| ------------------------------------------------------|\n");
    printf("|   -bd    | Binary to decimal      | 11111111111111111111111111111111111111111111111111111 |\n");
    printf("|   -bh    | Binary to hexadecimal  | Unlimited.                                            |\n");
    printf("|   -db    | Decimal to binary      | 9199999999999999999                                   |\n");
    printf("|   -dh    | Decimal to hexadecimal | 4294967295                                            |\n");
    printf("|   -hb    | Hexadecimal to binary  | Unlimited.                                            |\n");
    printf("|   -hd    | Hexadecimal to decimal | FFFFFFFFFFFFF                                         |\n");
    printf("---------------------------------------------------------------------------------------------\n\n");
    printf("hexc can be fed several strings, separated by whitespace. For example:\n\n");  
    printf("| ~$ hexc -bd 10101 111\n| 10101 -> 21\n| 111 -> 7\n");
}