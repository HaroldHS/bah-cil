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

ast_node parse_konstanta(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_KONSTANTA_ERR, sizeof(result.error_msg)-1);

    token curr_token = scan_token(input);
    consume_next_if_current_string_match(&curr_token, ALFABET, "konstanta");
    consume_next_if_current_type_match(&curr_token, SPASI);
    consume_next_if_current_type_match(&curr_token, KATA_KUNCI_TIPE_DATA);
    consume_next_if_current_type_match(&curr_token, SPASI);
    if (curr_token.type != ALFABET) {
        return result;
    }
    result.value[0] = curr_token; /* variable name */

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

ast_node parse_ekspresi_aritmatika(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_EKSP_ARITMATIKA_ERR, sizeof(result.error_msg)-1);

    return result;
}

ast_node parse_istilah(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_ISTILAH_ERR, sizeof(result.error_msg)-1);

    return result;
}

ast_node parse_faktor(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_FAKTOR_ERR, sizeof(result.error_msg)-1);

    /* first case, "variabel" spasi nama */
    token curr_token = scan_token(input);
    consume_next_if_current_string_match(&curr_token, ALFABET, "variabel");
    consume_next_if_current_type_match(&curr_token, SPASI);
    if (curr_token.type == NAMA) {
        result.type = FAKTOR;
        result.value[0] = curr_token;
        strncpy(result.error_msg, "\0", 1);
        return result;
    }

    /* second case, angka_bulat. restart from first input */
    curr_token = scan_token(input);
    if (curr_token.type == ANGKA_BULAT) {
        result.type = FAKTOR;
        result.value[0] = curr_token;
        strncpy(result.error_msg, "\0", 1);
        return result;
    }

    /* third case, ekspresi_aritmatika. restart from first input */
    // TODO: call parse_ekspresi_aritmatika();

    /* forth case, negation. restart from first input */
    // TODO: negate & call parse_faktor

    return result;
}

