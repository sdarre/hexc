#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define MIN_BASE 2
#define MAX_BASE 36


void ArgumentParser(char * args[], int size);
void Convert(char * input, int iBase, int oBase);
unsigned long iConvert(char * input, int iBase);
char * oConvert(unsigned long input, int oBase);
void PrintHelp();


int main (int argc, char *argv[]) {

    if (argc <= 1) {
        PrintHelp();
        return 0;
    }

    ArgumentParser(argv, (argc - 2));
    
    return 0;
}


int valid = 1;
void Convert(char * input, int iBase, int oBase) {

    if (iBase < MIN_BASE || iBase > MAX_BASE || oBase < MIN_BASE || oBase > MAX_BASE) {
        printf("Bases must be between 2 and 36 (inclusive).\n");
        exit(0);
    }

    printf("%s -> ", input);

    unsigned long l = iConvert(input, iBase);
    char * s;

    if (l == 0) {
        printf("0");
    }
    else if (valid++) {
        s = oConvert(l, oBase);
        for (int i = strlen(s); i >= 0; i--) {
            printf("%c", s[i]);
        }
        free(s);
        s = NULL;
    }
    printf("\n");
}


unsigned long iConvert(char * input, int iBase) {


    unsigned long result = 0;
    unsigned long maxVal = ULONG_MAX / iBase;
    int maxDigit = ULONG_MAX % iBase;

    for (;;) {
        int c = *input++;
        
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } 
        else if (c >= 'A' && (c < ('A' - 10 + iBase)) && iBase > 10) {
            digit = c - 'A' + 10;
        } 
        else if (c >= 'a' && (c < ('a' - 10 + iBase)) && iBase > 10) {
            digit = c - 'a' + 10;
        } 
        else {
            if (c != 0) {
                printf("Invalid input string.");
                valid = 0;
                return -1;
            }
            break;
        }
        if (digit >= iBase) {
            break;
        }
        if (result > maxVal || (result == maxVal && digit > maxDigit)) {
            printf("Input value too large.");
            valid = 0;
            return -1;
        }
        result = result * iBase + digit;
    }
    return result;
}


char * oConvert(unsigned long input, int oBase) {
    
    char * vector = malloc(sizeof(char) * 64);
    if (!vector) {
        printf("Memory error.\n");
        exit(0);
    }

    int i = 0;
    while (input > 0) {
        char c;
        unsigned long n = input % oBase;
        input = input / oBase;
        if (n < 10) {
            c = n + '0';
        }
        else {
            c = n + 'A' - 10;
        }
        vector[i++] = c;
    }
    return vector;
}


void ArgumentParser(char * args[], int size) {

    if (!strncmp(args[1], "-i", 2) && !strncmp(args[2], "-o", 2)) {
        size--;
        char iBase[3], oBase[3];
        strncpy(iBase, args[1] + 2, strlen(args[1]) - 1);
        strncpy(oBase, args[2] + 2, strlen(args[2]) - 1);
        for (int i = 0; i < size; i++) {
            Convert(args[3 + i], atoi(iBase), atoi(oBase));
        }
    }

    else if (!strncmp(args[1], "-h", 2) || !strncmp(args[1], "--help", 6)) {
        PrintHelp(); 
    }

    else {
        int iBase, oBase;

             if (!strncmp(args[1], "-bd", 4)) { iBase = 2;  oBase = 10; }
        else if (!strncmp(args[1], "-bh", 4)) { iBase = 2;  oBase = 16; }
        else if (!strncmp(args[1], "-bo", 4)) { iBase = 2;  oBase = 8;  }
        else if (!strncmp(args[1], "-db", 4)) { iBase = 10; oBase = 2;  }
        else if (!strncmp(args[1], "-dh", 4)) { iBase = 10; oBase = 16; }
        else if (!strncmp(args[1], "-do", 4)) { iBase = 10; oBase = 8;  }
        else if (!strncmp(args[1], "-hb", 4)) { iBase = 16; oBase = 2;  }
        else if (!strncmp(args[1], "-hd", 4)) { iBase = 16; oBase = 10; }
        else if (!strncmp(args[1], "-ho", 4)) { iBase = 16; oBase = 8;  }
        else if (!strncmp(args[1], "-ob", 4)) { iBase = 8;  oBase = 2;  }
        else if (!strncmp(args[1], "-od", 4)) { iBase = 8;  oBase = 10; }
        else if (!strncmp(args[1], "-oh", 4)) { iBase = 8;  oBase = 16; }
        else { printf("Invalid argument.\n"); }

        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], iBase, oBase);
        }
    }
}


void PrintHelp() {
    printf("Run \"hexc {operator} {string1 string2 string3...}\"\n");
    printf("or \"hexc {-i[input base size] -o[output base size] {string1 string2 string3...}\"\n");
    printf("to produce a converted string or series of strings.\n");
    printf("The operators are as follows:\n\n");
    printf("| Operator |      Description       |\n");
    printf("|   -bd    | Binary to decimal      |\n");
    printf("|   -bh    | Binary to hexadecimal  |\n");
    printf("|   -bo    | Binary to octal        |\n");
    printf("|   -db    | Decimal to binary      |\n");
    printf("|   -dh    | Decimal to hexadecimal |\n");
    printf("|   -do    | Decimal to octal       |\n");
    printf("|   -hb    | Hexadecimal to binary  |\n");
    printf("|   -hd    | Hexadecimal to decimal |\n");
    printf("|   -ho    | Hexadecimal to octal   |\n");
    printf("|   -ob    | Octal to binary        |\n");
    printf("|   -od    | Octal to decimal       |\n");
    printf("|   -oh    | Octal to hexadecimal   |\n\n");
    printf("Bases can range from 2 to 36 (inclusive).\n");
    printf("hexc can be fed several strings, separated by whitespace. For example:\n\n");  
    printf("| ~$ hexc -bd 10101 111\n| 10101 -> 21\n| 111 -> 7\n");
    printf("| ~$ hexc -i8 -o16 \n| 312 -> CA\n");
}
