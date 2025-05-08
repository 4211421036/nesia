#include <stdio.h>
#include "error.h"

void errorLexer(int line, const char *msg) {
    fprintf(stderr, "Kesalahan leksikal baris %d: %s\n", line, msg);
}

void errorParser(int line, const char *msg) {
    fprintf(stderr, "Kesalahan sintaks baris %d: %s\n", line, msg);
}

void errorRuntime(int line, const char *msg) {
    fprintf(stderr, "Kesalahan runtime baris %d: %s\n", line, msg);
}
