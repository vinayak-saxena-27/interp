#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

static Node *alloc_node(NodeType type) {
    Node *n = malloc(sizeof *n);
    if (n == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    n->type = type;
    return n;
}

Node *new_binary(TokenType op, Node *left, Node *right) {
    Node *n = alloc_node(NODE_BINARY);
    n->as.binary.op = op;
    n->as.binary.left = left;
    n->as.binary.right = right;
    return n;
}

Node *new_unary(TokenType op, Node *operand) {
    Node *n = alloc_node(NODE_UNARY);
    n->as.unary.op = op;
    n->as.unary.operand = operand;
    return n;
}

Node *new_number(double value) {
    Node *n = alloc_node(NODE_NUMBER);
    n->as.number = value;
    return n;
}

void free_node(Node *n) {
    if (n == NULL) return;
    
    switch (n->type) {
        case NODE_NUMBER:
            break;
        case NODE_UNARY:
            free_node(n->as.unary.operand);
            break;
        case NODE_BINARY:
            free_node(n->as.binary.left);
            free_node(n->as.binary.right);
            break;
    }
    free(n);
}