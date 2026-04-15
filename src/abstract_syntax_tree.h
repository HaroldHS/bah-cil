#ifndef abstract_syntax_tree_h
#define abstract_syntax_tree_h

#include <stdbool.h>
#include "grammar_enum.h"

typedef struct {
    TERMINAL    terminal_type;
    char        *value;
    int         value_length;
    struct      ast_node *left;
    struct      ast_node *right;
} ast_node;

#endif
