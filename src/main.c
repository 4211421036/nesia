// main.c
#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "error.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Penggunaan: nesia <berkas.ns>\n");
        return 1;
    }
    const char *filename = argv[1];
    // Baca seluruh file ke memori
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Tidak dapat membuka berkas '%s'\n", filename);
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *source = malloc(len+1);
    fread(source, 1, len, fp);
    source[len] = '\0';
    fclose(fp);

    // Analisis leksikal & sintaks
    Parser parser;
    initParser(&parser, source);
    AstNode *program = parseProgram(&parser);

    // Eksekusi AST
    interpret(program);
    return 0;
}
