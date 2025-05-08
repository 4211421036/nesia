#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "cli.h"
#include "parser.h"
#include "interpreter.h"

#ifndef GUI_MODE
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Penggunaan: nesia <berkas.ns>\n");
        return 1;
    }
    const char *filename = argv[1];
    
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Tidak dapat membuka berkas '%s'\n", filename);
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp); // Deklarasi 'len' dipindah ke sini
    fseek(fp, 0, SEEK_SET);
    char *source = malloc(len + 1);
    fread(source, 1, len, fp);
    source[len] = '\0';
    fclose(fp);

    Parser parser;
    initParser(&parser, source);
    AstNode *program = parseProgram(&parser);

    interpret(program);
    free(source);
    return 0;
}
#endif
