#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t i = 0;
int8_t mem[30000];

void usage(char *arg0, char *message) {
    fprintf(stderr, "%s\n", message);
    fprintf(stderr, "Usage: %s <file>\n", arg0);
    exit(1);
    return;
}

int32_t processChar(FILE *input, char *out);

// Returns the number of characters used/skipped
int32_t whileLoop(FILE *input) {
    int32_t processed;
    do {
        processed = 0;
        char c = '\0';
        do {
            processed += processChar(input, &c);
        } while (c != ']');
        if (mem[i] != 0) {
            fseek(input, -processed, SEEK_CUR);
        }
    } while (mem[i] != 0);

    return processed;
}

// Returns the number of characters used/skipped
int32_t processChar(FILE *input, char *out) {
    int c = *out = fgetc(input);
    if (c == EOF) {
        return 0;
    }
    int32_t chars = 1;
    switch (c) {
    case '>': i++; break;
    case '<': i--; break;
    case '+': mem[i]++; break;
    case '-': mem[i]--; break;
    case ',': mem[i] = getchar(); break;
    case '.': putchar(mem[i]); break;
    case '[': chars = whileLoop(input); break;
    case ']':
    default: break; // other characters considered comments
    }
    return chars;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage(argv[0], "Wrong number of arguments.");
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        usage(argv[0], "Input file not found.");
    }
    char c;
    while (processChar(input, &c) != 0)
        ;
    fclose(input);
    return 0;
}
