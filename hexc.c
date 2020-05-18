#include <stdio.h>
#include <string.h>
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
        if ((c >= '0' && c <= '9' && iBase >= 10) || (c >= '0' && c <= ('0' - 1 + iBase))) {
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

    if (!strncmp(args[1], "-i", 2) && size > 0) { 
        if (!strncmp(args[2], "-o", 2)) {
               
            if (strlen(args[1]) < 3 || strlen(args[2]) < 3) {
                printf("Invalid argument. See \"hexc --help\".\n"); 
                return;
            } 

            size--;
            char iBase[3], oBase[3];
            strncpy(iBase, args[1] + 2, strlen(args[1]) - 1);
            strncpy(oBase, args[2] + 2, strlen(args[2]) - 1);

            if (atoi(iBase) < MIN_BASE || atoi(iBase) > MAX_BASE || atoi(oBase) < MIN_BASE || atoi(oBase) > MAX_BASE) {
                printf("Bases must be between 2 and 36 (inclusive). See \"hexc --help\".\n");
                return;
            }

            if (size < 1) {
                printf("No input values passed. See \"hexc --help\".\n");
                return;
            }

            for (int i = 0; i < size; i++) {
                Convert(args[3 + i], atoi(iBase), atoi(oBase));
            }
        }
    }

    else if (!strncmp(args[1], "-h", 3) || !strncmp(args[1], "--help", 6)) {
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
        else { 
            printf("Invalid argument. See \"hexc --help\".\n"); 
            return;
        }

        if (size < 1) {
            printf("No input values passed. See \"hexc --help\".\n");
            return;
        }

        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], iBase, oBase);
        }
    }
}


void PrintHelp() {
    printf("Usage:\n");
    printf("    hexc [Option] [String(s)]\n\n");
    printf("Options:\n");
    printf("    -i[input base] -o[output base]      Convert from input base to output base\n");
    printf("    -bd      Convert from binary to decimal\n");
    printf("    -bh      Convert from binary to hexadecimal\n");
    printf("    -bo      Convert from binary to octal\n");
    printf("    -db      Convert from decimal to binary\n");
    printf("    -dh      Convert from decimal to hexadecimal\n");
    printf("    -do      Convert from decimal to octal\n");
    printf("    -hb      Convert from hexadecimal to binary\n");
    printf("    -hd      Convert from hexadecimal to decimal\n");
    printf("    -ho      Convert from hexadecimal to octal\n");
    printf("    -ob      Convert from octal to binary\n");
    printf("    -od      Convert from octal to decimal\n");
    printf("    -oh      Convert from octal to hexadecimal\n\n");
    printf("Bases can range from 2 to 36. hexc can be fed several strings, separated by whitespace.\n");
    printf("The maximum input value for any given string is 18446744073709551615 in decimal.\n\n");
    printf("Examples:\n");
    printf("    ~$ hexc -bd 10101 111\n");
    printf("    10101 -> 21\n");
    printf("    111 -> 7\n");
    printf("    ~$ hexc -i8 -o16 312\n");
    printf("    312 -> CA\n");
}