#include <stdio.h>
#include "lexer.h"

static const char *token_names[] = {
    [TOK_NUMBER] = "NUMBER",
    [TOK_PLUS] = "PLUS",
    [TOK_MINUS] = "MINUS",
    [TOK_STAR] = "STAR",
    [TOK_SLASH] = "SLASH",
    [TOK_L_PAREN] = "L_PAREN",
    [TOK_R_PAREN] = "R_PAREN",
    [TOK_EOF] = "EOF",
    [TOK_ERROR] = "ERROR",
};

int main(void) {
    char line[1024];

    for (;;) {
        printf("> ");
        if (!fgets(line, sizeof line, stdin)) {
            printf("\n");
            break;
        }

        Lexer lx;
        lexer_init(&lx, line);

        Token t;
        do {
            t = lexer_next(&lx);
            printf("%-8s '%.*s'\n", token_names[t.type], t.length, t.start);
        } while (t.type != TOK_EOF);
    }
    return 0;
}