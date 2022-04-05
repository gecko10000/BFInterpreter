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

int32_t processChar(FILE *input);

// Returns the number of characters used/skipped
int32_t whileLoop(FILE *input) {
    int32_t processed;
    do {
        processed = 0;
        int32_t chars;
        do {
            chars = processChar(input);
            processed += chars;
        } while (chars != 0);
        // since chars == 0 when we find ], we must add 1 to the total.
        processed++;
        if (mem[i] != 0) {
            fseek(input, -processed, SEEK_CUR);
        }
    } while (mem[i] != 0);

    return processed + 1; // must include initial [
}

// Returns the number of characters used/skipped
int32_t processChar(FILE *input) {
    int c = fgetc(input);
    if (c == EOF) {
        return 0;
    }
    int32_t chars = 1; // default
    switch (c) {
    case '>': i++; break;
    case '<': i--; break;
    case '+': mem[i]++; break;
    case '-': mem[i]--; break;
    case ',': mem[i] = getchar(); break;
    case '.': printf("%c", mem[i]); break;
    case '[': chars = whileLoop(input); break;
    case ']': chars = 0; // signal end of loop
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
    while (processChar(input) != 0) // EOF returns 0
        ;
    fclose(input);
    return 0;
}
