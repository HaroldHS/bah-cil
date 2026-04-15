#ifndef abstract_syntax_tree_h
#define abstract_syntax_tree_h

#include <stdbool.h>
#include "grammar_enum.h"
#include "lexer/lexer.h"

typedef struct {
    EXPRESSION type;
    token      value[MAX_TOKEN_IN_ONE_AST_NODE];
    struct     ast_node *left;
    struct     ast_node *right;
    char       error_msg[ERR_MSG_MAX_LEN];
} ast_node;

#endif
