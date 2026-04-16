#include <stdio.h>
#include <string.h>

#include "../grammar_enum.h"
#include "../lexer/lexer.h"
#include "parser.h"

ast_node parse_variabel(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_VARIABEL_ERR, sizeof(result.error_msg)-1);

    token curr_token = scan_token(input);
    consume_next_if_current_string_match(&curr_token, ALFABET, "variabel");
    consume_next_if_current_type_match(&curr_token, SPASI);
    consume_next_if_current_type_match(&curr_token, KATA_KUNCI_TIPE_DATA);
    consume_next_if_current_type_match(&curr_token, SPASI);
    if (curr_token.type == ALFABET) {
        result.value[0] = curr_token;
    } /* variable name */

    curr_token = scan_token(curr_token.next);
    consume_next_if_current_type_match(&curr_token, SPASI);
    consume_next_if_current_string_match(&curr_token, SIMBOL, "=");
    consume_next_if_current_type_match(&curr_token, SPASI);
    if ((curr_token.type != ANGKA_BULAT) && (curr_token.type != BOOLEAN) && (curr_token.type != UNTAIAN)) {
        return result;
    }
    result.value[1] = curr_token; /* variable value */

    curr_token = scan_token(curr_token.next);
    if (curr_token.type == BERHENTI) {
        result.type = VARIABEL;
        strncpy(result.error_msg, "\0", 1);
    }
    return result;
}

ast_node parse_constant(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_KONSTANTA_ERR, sizeof(result.error_msg)-1);

    token curr_token = scan_token(input);
    consume_next_if_current_string_match(&curr_token, ALFABET, "konstanta");
    consume_next_if_current_type_match(&curr_token, SPASI);
    consume_next_if_current_type_match(&curr_token, KATA_KUNCI_TIPE_DATA);
    consume_next_if_current_type_match(&curr_token, SPASI);
    if (curr_token.type == ALFABET) {
        result.value[0] = curr_token;
    } /* variable name */

    curr_token = scan_token(curr_token.next);
    consume_next_if_current_type_match(&curr_token, SPASI);
    consume_next_if_current_string_match(&curr_token, SIMBOL, "=");
    consume_next_if_current_type_match(&curr_token, SPASI);
    if ((curr_token.type != ANGKA_BULAT) && (curr_token.type != BOOLEAN) && (curr_token.type != UNTAIAN)) {
        return result;
    }
    result.value[1] = curr_token; /* variable value */

    curr_token = scan_token(curr_token.next);
    if (curr_token.type == BERHENTI) {
        result.type = KONSTANTA;
        strncpy(result.error_msg, "\0", 1);
    }
    return result;
}
