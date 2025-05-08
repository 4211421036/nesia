// parser.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "error.h"

static void advance(Parser *parser) {
    parser->current = nextToken(&parser->lexer);
}

static int match(Parser *parser, TokenType type) {
    if (parser->current.type == type) {
        advance(parser);
        return 1;
    }
    return 0;
}

AstNode* parseStatement(Parser *parser) {
    // Contoh parsing fungsi cetak
    if (parser->current.type == TOK_KATA_KUNCI &&
        strcmp(parser->current.lexeme, "perintah") == 0) {
        // misal: perintah cetak("Halo");
        advance(parser); // lewat 'perintah'
        if (match(parser, TOK_IDENT) && strcmp(parser->current.lexeme, "cetak")==0) {
            advance(parser); // lewat 'cetak'
            // Parsing "(" <ekspresi> ")"
            // ...
            // Buat AST node cetak
            AstNode *node = createPrintNode(/*...*/);
            return node;
        }
    }
    // contoh parsing penugasan instruksi
    if (parser->current.type == TOK_KATA_KUNCI &&
        strcmp(parser->current.lexeme, "instruksi") == 0) {
        advance(parser); // lewat 'instruksi'
        if (parser->current.type == TOK_IDENT) {
            char *nama = strdup(parser->current.lexeme);
            advance(parser);
            // harapkan simbol '='
            if (!match(parser, TOK_OPERATOR) || strcmp(parser->current.lexeme, "=")!=0) {
                parserError(parser->current.line, "Diharapkan '=' setelah nama variabel");
            }
            advance(parser); // lewat '='
            // parse ekspresi, dan harus diakhiri ';'
            AstNode *expr = parseExpression(parser);
            // ...
            AstNode *assign = createAssignNode(nama, expr);
            return assign;
        }
    }
    // Jika tidak ada pola dikenali, lempar kesalahan sintaks
    parserError(parser->current.line, "Pernyataan tidak dikenal");
    return NULL;
}

AstNode* parseProgram(Parser *parser) {
    advance(parser); // dapatkan token pertama
    AstNode *root = createBlockNode();
    while (parser->current.type != TOK_EOF) {
        AstNode *stmt = parseStatement(parser);
        addChild(root, stmt);
    }
    return root;
}
