#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX_UINT 4294967295


void BinToDec(char *input[], int size);
void BinToHex(char *input[], int size);
void DecToBin(char *input[], int size);
void DecToHex(char *input[], int size);
void HexToBin(char *input[], int size);
void HexToDec(char *input[], int size);
void PrintHelp();


int main (int argc, char *argv[]) {

    if (argc <= 1) {
        printf("No arguments provided. Run \"hexc -h\" or \"hexc --help\" for help.\n");
        exit(0);
    }
    int size = argc - 2;
    char * input[size];
    char * conv = argv[1];
    
    for (int i = 2; i < argc; i++) {
        input[i - 2] = argv[i];
    }

    if (!strncmp(conv, "-bd", 4)) { BinToDec(input, size); }
    else if (!strncmp(conv, "-bh", 4)) { BinToHex(input, size); }
    else if (!strncmp(conv, "-db", 4)) { DecToBin(input, size); }
    else if (!strncmp(conv, "-dh", 4)) { DecToHex(input, size); }
    else if (!strncmp(conv, "-hb", 4)) { HexToBin(input, size); }
    else if (!strncmp(conv, "-hd", 4)) { HexToDec(input, size); }
    else if (!strncmp(conv, "-h", 2) || !strncmp(conv, "--help", 6)) { PrintHelp(); }
    else { printf("Invalid argument.\n"); }

    return 0;
}


void BinToDec(char *input[], int size) {
    unsigned long result = 0;
    for (int i = 0; i < size; i++) {
        int power = 0, valid = 1;
        printf("%s -> ", input[i]);
        for (int k = strlen(input[i]) - 1; k >= 0; k--) {
            if (power > 52) {
                printf("Binary value too large.\n");
                valid--;
                break;
            }
            if ((input[i][k] - '0') == 1) {
                result += pow(2, power);
            }
            else if ((input[i][k] - '0') != 0) {
                printf("Input not in binary form.\n");
                valid--;
                break;
            }
            power++;        
        }
        if (valid) printf("%lu\n", result);
        result = 0;
    }
}


void BinToHex(char *input[], int size) {
    for (int i = 0; i < size; i++) {
        int power = 0, byte = 0, counter = 0;
        char * str = (char *) malloc(sizeof(char) * strlen(input[i]));
        if (!str) {
            printf("Memory error.\n");
            exit(0);
        }
        printf("%s -> ", input[i]);
        for (int k = strlen(input[i]) - 1; k >= 0; k--) {
            if ((input[i][k] - '0') == 1) {
                byte += pow(2, power);
            }
            else if ((input[i][k] - '0') != 0) {
                printf("Input not in binary form.");
                break;
            }
            power++;
            if (power == 4 || k == 0) {
                if (byte > 9) { 
                    byte += ('A' - 10); 
                }
                else { 
                    byte += '0'; 
                }
                if (!(byte == '0' && k == 0)) {
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
    }
}


void DecToBin(char *input[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s -> ", input[i]);
        int vector[64];
        unsigned long num = atol(input[i]);
        if (num == 0) {
            printf("0\n");
            continue;
        }
        int n = 0;
        while (num > 0) {
            vector[n] = num % 2;
            num = num / 2;
            n++;
        }
        for (int k = n - 1; k >= 0; k--) {
            printf("%d", vector[k]);
        }
        printf("\n");
    }
}


void DecToHex(char *input[], int size) {
    for (int i = 0; i < size; i++) {
        if (atol(input[i]) > MAX_UINT) {
            printf("%s -> Decimal value too large.\n", input[i]);
            continue;
        }
        printf("%s -> %lX\n", input[i], atol(input[i]));
    }
}


void HexToBin(char *input[], int size) {
    for (int i = 0; i < size; i++) {
        int valid = 1;
        printf("%s -> ", input[i]);
        for (int k = 0; k < strlen(input[i]); k++) {
            if (!(input[i][k] > ('0' - 1) && input[i][k] < ('9' + 1)) 
             && !(input[i][k] > ('A' - 1) && input[i][k] < 'G') 
             && !(input[i][k] > ('a' - 1) && input[i][k] < 'g')) {
                printf("Input not in hexadecimal form.");
                valid--;
                break;
            }
        }
        for (int k = 0; k < strlen(input[i]) && valid; k++) {
            switch(input[i][k]){
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
}


void HexToDec(char *input[], int size) {
    for (int i = 0; i < size; i++) {
        long result = 0;
        int power = 0, valid = 1;
        if (strlen(input[i]) > 13) {
            printf("%s -> Hexadecimal value too large.\n", input[i]);
            continue;
        }
        for (int k = (strlen(input[i]) - 1); k >= 0; k--) {
            if (input[i][k] > ('0' - 1) && input[i][k] < ('9' + 1)) {
                result += (input[i][k] - '0') * pow(16, power++);
            }
            else if (input[i][k] > ('A' - 1) && input[i][k] < 'G') {
                result += (input[i][k] - ('A' - 10)) * pow(16, power++);
            }
            else if (input[i][k] > ('a' - 1) && input[i][k] < 'g') {
                result += (input[i][k] - ('a' - 10)) * pow(16, power++);
            }
            else {
                printf("%s -> Input not in hexadecimal form.\n", input[i]);
                valid--;
                break;
            }
        }
        if (valid) printf("%s -> %ld\n", input[i], result);
    }
}


void PrintHelp() {
    printf("\nRun \"hexc {operator} {string1 string2 string3...}\" to produce a converted string or series of strings.\n");
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
    printf("| ~$ hexc -bd 10101 111\n| 10101 -> 21\n| 111 -> 7\n\n");
}