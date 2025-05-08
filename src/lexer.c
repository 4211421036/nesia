// lexer.c
#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

void initLexer(Lexer *lexer, const char *text) {
    lexer->src = text;
    lexer->pos = 0;
    lexer->line = 1;
}

static char peek(Lexer *lexer) {
    return lexer->src[lexer->pos];
}
static char advance(Lexer *lexer) {
    char c = lexer->src[lexer->pos++];
    if (c == '\n') lexer->line++;
    return c;
}
static void skipWhitespace(Lexer *lexer) {
    for (;;) {
        char c = peek(lexer);
        if (c==' '||c=='\r'||c=='\t') { advance(lexer); }
        else if (c=='\n') { advance(lexer); }
        else break;
    }
}
Token nextToken(Lexer *lexer) {
    skipWhitespace(lexer);
    Token token;
    token.lexeme = NULL;
    token.line = lexer->line;
    char c = peek(lexer);
    if (c == '\0') {
        token.type = TOK_EOF;
        return token;
    }
    if (c == '%') { // komentar
        while (peek(lexer)!='\n' && peek(lexer)!='\0') advance(lexer);
        return nextToken(lexer);
    }
    if (isalpha(c)) { // identifier atau kata kunci
        size_t start = lexer->pos;
        while (isalnum(peek(lexer)) || peek(lexer)=='_') advance(lexer);
        size_t len = lexer->pos - start;
        char *text = strndup(lexer->src + start, len);
        // contoh cek kata kunci sederhana
        if (strcmp(text, "perintah")==0 || strcmp(text, "instruksi")==0) {
            token.type = TOK_KATA_KUNCI;
        } else {
            token.type = TOK_IDENT;
        }
        token.lexeme = text;
        return token;
    }
    if (isdigit(c)) { // angka
        size_t start = lexer->pos;
        while (isdigit(peek(lexer))) advance(lexer);
        size_t len = lexer->pos - start;
        token.type = TOK_ANGKA;
        token.lexeme = strndup(lexer->src + start, len);
        return token;
    }
    if (c == '"') { // string literal
        advance(lexer); // lewati tanda petik
        size_t start = lexer->pos;
        while (peek(lexer) != '"' && peek(lexer)!='\0') advance(lexer);
        size_t len = lexer->pos - start;
        token.type = TOK_STRING;
        token.lexeme = strndup(lexer->src + start, len);
        if (peek(lexer) == '"') advance(lexer);
        return token;
    }
    // tanda baca dan operator sederhana
    if (strchr("=+-*/();{}", c)) {
        token.type = (ispunct(c) ? TOK_OPERATOR : TOK_PUNCT);
        token.lexeme = strndup(lexer->src + lexer->pos, 1);
        advance(lexer);
        return token;
    }
    // karakter tidak dikenali => kesalahan
    char bad = advance(lexer);
    token.type = TOK_ERROR;
    token.lexeme = strndup(&bad, 1);
    return token;
}
