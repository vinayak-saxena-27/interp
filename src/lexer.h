#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOK_NUMBER,
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_L_PAREN, TOK_R_PAREN,
    TOK_EOF, TOK_ERROR
} TokenType;

typedef struct {
    TokenType type;
    const char *start;
    int length;
    int line;
} Token;

typedef struct {
    const char *start;
    const char *current;
    int line;
} Lexer;

void lexer_init(Lexer *lx, const char * source);
Token lexer_next(Lexer *lx);
#endif