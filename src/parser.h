// parser.h
#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Lexer lexer;
    Token current;
} Parser;

void initParser(Parser *parser, const char *source);
AstNode* parseProgram(Parser *parser);

#endif
