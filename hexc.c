#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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


void Convert(char * input, int iBase, int oBase) {

    if (iBase < 2 || iBase > 36 || oBase < 2 || oBase > 36) {
        printf("Bases must be between 2 and 36 (inclusive).\n");
        return;
    }

    printf("%s -> ", input);

    unsigned long l = iConvert(input, iBase);
    char * s;

    if (l != -1) {
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
    int power = 0;

    for (int i = (strlen(input) - 1); i >= 0; i--) {
        if ((input[i] > ('0' - 1)) && (input[i] < ('9' + 1))) {
            result += (input[i] - '0') * pow(iBase, power++);
        }
        else if ((((input[i] > ('A' - 1)) && (input[i] < ('Z' + 1))) || ((input[i] > ('a' - 1)) && (input[i] < ('z' + 1)))) && iBase > 10) {
            result += (input[i] - ('A' - 10)) * pow(iBase, power++);
        }
        else {
            printf("Invalid input string.");
            return -1;
        }
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
        int n = input % oBase;
        input = input / oBase;
        if (n < 10) {
            c = n + '0';
        }
        else {
            c = n + ('A' - 10);
        }
        vector[i++] = c;
    }
    return vector;
}


void ArgumentParser(char * args[], int size) {

    if (!strncmp(args[1], "-i", 2) && !strncmp(args[2], "-o", 2)) {
        size--;
        char iBase[3];
        char oBase[3];
        strncpy(iBase, args[1] + 2, strlen(args[1]) - 1);
        strncpy(oBase, args[2] + 2, strlen(args[2]) - 1);
        for (int i = 0; i < size; i++) {
            Convert(args[3 + i], atoi(iBase), atoi(oBase));
        }
    }

    else if (!strncmp(args[1], "-bd", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 2, 10);
        }
    }

    else if (!strncmp(args[1], "-bh", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 2, 16);
        }        
    }

    else if (!strncmp(args[1], "-bo", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 2, 8);
        }        
    }

    else if (!strncmp(args[1], "-hb", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 16, 2);
        }        
    }

    else if (!strncmp(args[1], "-hd", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 16, 10);
        }        
    }

    else if (!strncmp(args[1], "-ho", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 16, 8);
        }        
    }

    else if (!strncmp(args[1], "-db", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 10, 2);
        }        
    }

    else if (!strncmp(args[1], "-dh", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 10, 16);
        }        
    }

    else if (!strncmp(args[1], "-do", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 10, 8);
        }        
    }

    else if (!strncmp(args[1], "-ob", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 8, 2);
        }        
    }

    else if (!strncmp(args[1], "-od", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 8, 10);
        }        
    }

    else if (!strncmp(args[1], "-oh", 4)) {
        for (int i = 0; i < size; i++) {
            Convert(args[2 + i], 8, 16);
        }        
    }

    else if (!strncmp(args[1], "-h", 2) || !strncmp(args[1], "--help", 6)) {
        PrintHelp(); 
    }

    else {
        printf("Invalid argument.\n");
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