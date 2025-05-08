#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "error.h"

static void advance(Parser *parser) {
    parser->current = nextToken(&parser->lexer);
}

void parserError(int line, const char *msg) {
    errorParser(line, msg);
    exit(1);
}

AstNode* parseExpression(Parser *parser) {
    // Stub sederhana: jika token ANGKA, buat literal
    if (parser->current.type == TOK_ANGKA) {
        int val = atoi(parser->current.lexeme);
        AstNode *lit = createLiteralNode(val);
        advance(parser);
        return lit;
    }
    if (parser->current.type == TOK_IDENT) {
        AstNode *var = createVarNode(strdup(parser->current.lexeme));
        advance(parser);
        return var;
    }
    parserError(parser->current.line, "Ekspresi tidak dikenali");
    return NULL;
}

AstNode* parseStatement(Parser *parser) {
    // Contoh parsing print
    if (parser->current.type == TOK_KATA_KUNCI &&
        strcmp(parser->current.lexeme, "perintah") == 0) {
        advance(parser); // lewat 'perintah'
        if (parser->current.type == TOK_IDENT &&
            strcmp(parser->current.lexeme, "cetak") == 0) {
            advance(parser);
            if (parser->current.type != TOK_PUNCT || strcmp(parser->current.lexeme, "(") != 0)
                parserError(parser->current.line, "Diharapkan '('");
            advance(parser);
            AstNode *expr = parseExpression(parser);
            if (parser->current.type != TOK_PUNCT || strcmp(parser->current.lexeme, ")") != 0)
                parserError(parser->current.line, "Diharapkan ')'");
            advance(parser);
            if (parser->current.type != TOK_PUNCT || strcmp(parser->current.lexeme, ";") != 0)
                parserError(parser->current.line, "Diharapkan ';'");
            advance(parser);
            return createPrintNode("", expr);
        }
    }
    parserError(parser->current.line, "Pernyataan tidak dikenal");
    return NULL;
}

AstNode* parseProgram(Parser *parser) {
    advance(parser);
    AstNode *block = createBlockNode();
    while (parser->current.type != TOK_EOF) {
        AstNode *stmt = parseStatement(parser);
        addChild(block, stmt);
    }
    return block;
}
