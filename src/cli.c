#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "error.h"
#include "cli.h"

int runCLI(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Tidak dapat membuka berkas '%s'\n", filename);
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *source = malloc(len + 1);
    fread(source, 1, len, fp);
    source[len] = '\0';
    fclose(fp);

    Parser parser;
    initParser(&parser, source);
    AstNode *program = parseProgram(&parser);
    if (!program) return 1;

    interpret(program);
    return 0;
}
