#ifndef abstract_syntax_tree_h
#define abstract_syntax_tree_h

#include "grammar_enum.h"
#include "lexer/lexer.h"

typedef struct ast_node { /* allow self-referencing struct with named struct */
    char            *next_input; /* pointing to start of next input (token) */
    char            error_msg[ERR_MSG_MAX_LEN];
    struct ast_node *left;
    struct ast_node *right;
    token           value[MAX_TOKEN_IN_ONE_AST_NODE];
    EXPRESSION      type;
} ast_node;

#endif
