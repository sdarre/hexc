#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    int size = argc - 2;
    char * input[size];
    
    for (int i = 2; i < argc; i++) {
        input[i - 2] = argv[i];
    }

    char * conv = argv[1];

    // Binary -> Decimal
    if (!strncmp(conv, "-bd", 3)) { 
        long result = 0;
        for (int i = 0; i < size; i++) {
            int power = 0;
            printf("%s -> ", input[i]);
            for (int k = strlen(input[i]) - 1; k >= 0; k--) {
                if (power > 52) {
                    printf("Binary value too large.\n");
                    goto LOOP;
                }
                if ((input[i][k] - 48) == 1) {
                    result += pow(2, power);
                }
                else if ((input[i][k] - 48) != 0) {
                    printf("Input not in binary form.\n");
                    goto LOOP;
                }
                power++;        
            }
            printf("%lu\n", result);
            LOOP:result = 0;
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
            long vector[32];
            long num = atol(input[i]);
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
            if (atoi(input[i]) > 999999999) {
                printf("%s -> Decimal value too large.\n", input[i]);
            }
            else {
                printf("%s -> %X\n", input[i], atoi(input[i]));
            }
        }
    }

    // Hexadecimal -> Binary
    else if (!strncmp(conv, "-hb", 3)) {
        printf("Coming soon.\n");
    }

    // Hexadecimal -> Decimal
    else if (!strncmp(conv, "-hd", 3)) {
        printf("Coming soon.\n");
    }

    else {
        printf("Invalid conversion type.\n");
    }

    return 0;
}