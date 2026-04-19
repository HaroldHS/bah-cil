#ifndef parser_h
#define parser_h

#include "../abstract_syntax_tree.h"

ast_node parse_variabel(char *input);
ast_node parse_konstanta(char *input);
ast_node parse_ekspresi_aritmatika(char *input);
ast_node parse_istilah(char *input);
ast_node parse_faktor(char *input);

#endif
