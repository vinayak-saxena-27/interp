#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    NODE_NUMBER, NODE_UNARY, NODE_BINARY
} NodeType;

typedef struct Node Node;

struct Node {
    NodeType type;
    union {
        double number;
        struct { TokenType op; Node *operand; } unary;
        struct { TokenType op; Node *left; Node *right; } binary; 
    } as;
} ;

Node *new_number(double value);
Node *new_unary(TokenType op, Node *operand);
Node *new_binary(TokenType op, Node *left, Node *right);
void free_node(Node *node);

#endif