#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

void initParser(Parser *parser, const char *source);
AstNode* parseProgram(Parser *parser);
// Tambahan:
void parserError(int line, const char *msg);
AstNode* parseExpression(Parser *parser);

#endif
