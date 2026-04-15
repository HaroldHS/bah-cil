#ifndef abstract_syntax_tree_h
#define abstract_syntax_tree_h

#include <stdbool.h>
#include "grammar_enum.h"
#include "lexer/lexer.h"

typedef struct {
    token       tokens[MAX_TOKEN_IN_ONE_AST_NODE];
    EXPRESSION  expression_type;
    char        *value;
    int         value_length;
    struct      ast_node *left;
    struct      ast_node *right;
} ast_node;

#endif
