#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    if (argc <= 1) exit(0);
    int size = argc - 2;
    char * input[size];
    
    for (int i = 2; i < argc; i++) {
        input[i - 2] = argv[i];
    }

    char * conv = argv[1];

    // Binary -> Decimal
    if (!strncmp(conv, "-bd", 3)) { 
        unsigned long result = 0;
        for (int i = 0; i < size; i++) {
            int power = 0;
            printf("%s -> ", input[i]);
            for (int k = strlen(input[i]) - 1; k >= 0; k--) {
                if (power > 52) {
                    printf("Binary value too large.\n");
                    goto L1;
                }
                if ((input[i][k] - 48) == 1) {
                    result += pow(2, power);
                }
                else if ((input[i][k] - 48) != 0) {
                    printf("Input not in binary form.\n");
                    goto L1;
                }
                power++;        
            }
            printf("%lu\n", result);
            L1:result = 0;
        }
    }

    // Binary -> Hexadecimal
    else if (!strncmp(conv, "-bh", 3)) { 
        for (int i = 0; i < size; i++) {
            int power = 0, byte = 0, counter = 0;
            char * str = (char *) malloc(sizeof(char) * strlen(input[i]));
            printf("%s -> ", input[i]);
            for (int k = strlen(input[i]) - 1; k >= 0; k--) {
                if ((input[i][k] - 48) == 1) {
                    byte += pow(2, power);
                }
                else if ((input[i][k] - 48) != 0) {
                    printf("Input not in binary form.");
                    break;
                }
                power++;
                if (power == 4 || k == 0) {
                    if (byte > 9) { 
                        byte += 55; 
                    }
                    else { 
                        byte += 48; 
                    }
                    if (!(byte == 48 && k == 0)) {
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

    // Decimal -> Binary
    else if (!strncmp(conv, "-db", 3)) { 
        for (int i = 0; i < size; i++) {
            printf("%s -> ", input[i]);
            long vector[64];
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

    // Decimal -> Hexadecimal
    else if (!strncmp(conv, "-dh", 3)) {
        for (int i = 0; i < size; i++) {
            if (atol(input[i]) > 4294967295) {
                printf("%s -> Decimal value too large.\n", input[i]);
                continue;
            }
            if (1 > 0) {
                printf("%s -> %X\n", input[i], atol(input[i]));
            }
        }
    }

    // Hexadecimal -> Binary
    else if (!strncmp(conv, "-hb", 3)) {
        for (int i = 0; i < size; i++) {
            printf("%s -> ", input[i]);
            for (int k = 0; k < strlen(input[i]); k++) {
                if (!(input[i][k] > 47 && input[i][k] < 58) && !(input[i][k] > 64 && input[i][k] < 71) && !(input[i][k] > 96 && input[i][k] < 103)) {
                    printf("Input not in hexadecimal form.");
                    goto L2;
                }
            }
            for (int k = 0; k < strlen(input[i]); k++) {
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
            L2:printf("\n");
        }
    }

    // Hexadecimal -> Decimal
    else if (!strncmp(conv, "-hd", 3)) {
        for (int i = 0; i < size; i++) {
            long result = 0;
            int power = 0;
            if (strlen(input[i]) > 13) {
                printf("%s -> Hexadecimal value too large.\n", input[i]);
                continue;
            }
            for (int k = (strlen(input[i]) - 1); k >= 0; k--) {
                if (input[i][k] > 47 && input[i][k] < 58) {
                    result += (input[i][k] - 48) * pow(16, power++);
                }
                else if (input[i][k] > 64 && input[i][k] < 71) {
                    result += (input[i][k] - 55) * pow(16, power++);
                }
                else if (input[i][k] > 96 && input[i][k] < 103) {
                    result += (input[i][k] - 87) * pow(16, power++);
                }
                else {
                    printf("%s -> Input not in hexadecimal form.\n", input[i]);
                    break;
                }
            }
            printf("%s -> %ld\n", input[i], result);
        }
    }

    else {
        printf("Invalid conversion type.\n");
    }

    return 0;
}