#define _POSIX_C_SOURCE 200809L  // <-- TAMBAHKAN DI BARIS PALING ATAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

AstNode* createPrintNode(char *msg, AstNode *expr) {
    AstNode *node = malloc(sizeof(AstNode));
    node->type = AST_PRINT;
    node->text = strdup(msg);
    node->left = NULL;
    node->right = expr;
    node->next = NULL;
    return node;
}

AstNode* createAssignNode(char *varname, AstNode *expr) {
    AstNode *node = malloc(sizeof(AstNode));
    node->type = AST_ASSIGN;
    node->text = strdup(varname);
    node->left = NULL;
    node->right = expr;
    node->next = NULL;
    return node;
}

AstNode* createLiteralNode(int nilai) {
    AstNode *node = malloc(sizeof(AstNode));
    node->type = AST_LITERAL;
    char buffer[32];
    sprintf(buffer, "%d", nilai);
    node->text = strdup(buffer);
    node->left = node->right = node->next = NULL;
    return node;
}

AstNode* createVarNode(char *name) {
    AstNode *node = malloc(sizeof(AstNode));
    node->type = AST_VAR;
    node->text = strdup(name);
    node->left = node->right = node->next = NULL;
    return node;
}

AstNode* createBlockNode() {
    AstNode *node = malloc(sizeof(AstNode));
    node->type = AST_BLOCK;
    node->text = NULL;
    node->left = node->right = node->next = NULL;
    return node;
}

void addChild(AstNode *block, AstNode *stmt) {
    if (!block->left) {
        block->left = stmt;
    } else {
        AstNode *cur = block->left;
        while (cur->next) cur = cur->next;
        cur->next = stmt;
    }
}
