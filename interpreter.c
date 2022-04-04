#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int i = 0;
int8_t mem[30000];

void usage(char *arg0, char *message) {
    fprintf(stderr, "%s\n", message);
    fprintf(stderr, "Usage: %s <file>\n", arg0);
    exit(1);
    return;
}

void processChar(FILE *input) {
    int c = fgetc(input);
    if (c == EOF) {
        return;
    }
    switch (c) {
    case '>': i++; break;
    case '<': i--; break;
    case '+': mem[i]++; break;
    case '-': mem[i]--; break;
    default: continue; // other characters considered comments
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage(argv[0], "Wrong number of arguments.");
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        usage(argv[0], "Input file not found.");
    }
    int c;
    while ((c = fgetc(input)) != EOF) {
    }
    return 0;
}
