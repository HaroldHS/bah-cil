#ifndef parser_h
#define parser_h

#include "../abstract_syntax_tree.h"

ast_node parse_variabel(char *input);
ast_node parse_constant(char *input);

#endif
