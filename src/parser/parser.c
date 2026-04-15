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
    if (var.type != ALFABET){
        char var_word[var.length];
        sprintf(var_word, "%.*s", var.length, var.value);
        if (strncmp(var_word, "variabel", 8) != 0) {
            return result;
        } /* if not ALFABET type && value is not "variabel" then INVALID */
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
