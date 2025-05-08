// lexer.h
#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOK_EOF, TOK_ANGKA, TOK_STRING, TOK_IDENT,
    TOK_KATA_KUNCI, TOK_OPERATOR, TOK_PUNCT,
    TOK_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char *lexeme;    // isi token
    int line;        // nomor baris
} Token;

typedef struct {
    const char *src;
    size_t pos;
    int line;
} Lexer;

void initLexer(Lexer *lexer, const char *text);
Token nextToken(Lexer *lexer);

#endif
