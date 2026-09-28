#include <ctype.h>
#include "lexer.h"

void lexer_init(Lexer *lx, const char *source) {
    lx->start = source;
    lx->current = source;
    lx->line = 1;
}

static char peek(Lexer *lx) {
    return *lx->current;
}

static char peek_next(Lexer *lx) {
    if (*lx->current == '\0') return '\0';
    return lx->current[1];
}

static char advance(Lexer *lx) {
    return *lx->current++;
}

static Token make_token(Lexer *lx, TokenType type) {
    Token t;
    t.type = type;
    t.start = lx->start;
    t.length = (int)(lx->current - lx->start);
    t.line = lx->line;
    return t;
}

Token lexer_next(Lexer *lx) {
    while (isspace((unsigned char)peek(lx))) {
        if (peek(lx) == '\n') {
            lx->line++;
        }
        advance(lx);
    }
    lx->start = lx->current;
    if (peek(lx) == '\0') {
        return make_token(lx, TOK_EOF);
    }
    char c = advance(lx);
    switch (c) {
        case '+': return make_token(lx, TOK_PLUS);
        case '-': return make_token(lx, TOK_MINUS);
        case '*': return make_token(lx, TOK_STAR);
        case '/': return make_token(lx, TOK_SLASH);
        case '(': return make_token(lx, TOK_L_PAREN);
        case ')': return make_token(lx, TOK_R_PAREN);
        default:
            if (isdigit((unsigned char)c)) {
                while (isdigit((unsigned char)peek(lx))) {
                    advance(lx);
                }
                if (peek(lx) == '.' && isdigit((unsigned char)peek_next(lx))) {
                    advance(lx);
                    while (isdigit((unsigned char)peek(lx))) {
                        advance(lx);
                    }
                }
                return make_token(lx, TOK_NUMBER);
            }
            return make_token(lx, TOK_ERROR);
    }
}