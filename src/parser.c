#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

typedef struct {
    Lexer lexer;
    Token current;
    int had_error;
} Parser;

static Node *expression(Parser *p);

static void error_at(Parser *p, Token *t, const char *message) {
    if (p->had_error) return;
    p->had_error = 1;
    fprintf(stderr, "Error");
    if (t->type == TOK_EOF) {
        fprintf(stderr, " at end");
    } else {
        fprintf(stderr, " at '%.*s'", t->length, t->start);
    }
    fprintf(stderr, ": %s\n", message);
}