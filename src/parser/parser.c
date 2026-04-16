#include <stdio.h>
#include <string.h>

#include "../grammar_enum.h"
#include "../lexer/lexer.h"
#include "parser.h"

ast_node parse_variabel(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_VARIABEL_ERR, sizeof(result.error_msg)-1);

    token var = scan_token(input);
    bool is_var = check_token_string(&var, ALFABET, "variabel");
    if (!is_var) {
        return result;
    }

    token space = scan_token(var.next);
    if (space.type != SPASI) {
        return result;
    }

    token datatype = scan_token(space.next);
    if (datatype.type != KATA_KUNCI_TIPE_DATA) {
        return result;
    }

    space = scan_token(datatype.next);
    if (space.type != SPASI) {
        return result;
    }

    result.type = VARIABEL;
    strncpy(result.error_msg, "\0", 1);
    return result;
}

ast_node parse_constant(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;

    return result;
}
