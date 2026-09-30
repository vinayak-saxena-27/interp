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

static void error_at(Parser *p)