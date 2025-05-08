// interpreter.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "ast.h"
#include "error.h"
#include "nesia.h"

// Tabel variabel sederhana (asumsi variabel global)
#define MAX_VARS 100
char *var_names[MAX_VARS];
int var_values[MAX_VARS];
int var_count = 0;

int getVar(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_names[i], name) == 0) return var_values[i];
    }
    // Jika variabel belum ada, definisikan dengan 0
    var_names[var_count] = strdup(name);
    var_values[var_count] = 0;
    var_count++;
    return 0;
}

void setVar(const char *name, int value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_names[i], name) == 0) {
            var_values[i] = value;
            return;
        }
    }
    // Baru, simpan
    var_names[var_count] = strdup(name);
    var_values[var_count] = value;
    var_count++;
}

int evaluate(AstNode *node) {
    if (!node) return 0;
    switch (node->type) {
        case AST_LITERAL:
            return atoi(node->text);
        case AST_VAR:
            return getVar(node->text);
        // Ekspresi lainnya (misal AST_BINARY op +,*dst) di-skip contoh
        default:
            return 0;
    }
}

void execute(AstNode *node) {
    if (!node) return;
    if (node->type == AST_BLOCK) {
        for (AstNode *stmt = node->left; stmt; stmt = stmt->next) {
            execute(stmt);
        }
    } else if (node->type == AST_PRINT) {
        int val = evaluate(node->right); // asumsikan hanya ekspresi di kanan
        printf("%s%d\n", node->text, val); // mencetak teks + nilai
    } else if (node->type == AST_ASSIGN) {
        int val = evaluate(node->right);
        setVar(node->text, val);
    } else {
        // tipe AST lainnya...
    }
}

// Fungsi entry untuk menjalankan AST program
void interpret(AstNode *program) {
    execute(program);
}
