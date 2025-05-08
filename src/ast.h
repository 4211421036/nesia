// ast.h
#ifndef AST_H
#define AST_H

typedef enum { AST_PRINT, AST_ASSIGN, AST_LITERAL, AST_VAR, AST_BLOCK, /* dst */ } AstType;

typedef struct AstNode {
    AstType type;
    char *text;            // misal nama variabel, literal, pesan, dll.
    struct AstNode *left;  // anak kiri (ekspresi)
    struct AstNode *right; // anak kanan (opsional)
    struct AstNode *next;  // untuk list statement di block
} AstNode;

AstNode* createPrintNode(char *msg, AstNode *expr);
AstNode* createAssignNode(char *varname, AstNode *expr);
AstNode* createLiteralNode(int nilai);
AstNode* createVarNode(char *name);
AstNode* createBlockNode();
void addChild(AstNode *block, AstNode *stmt);

#endif
