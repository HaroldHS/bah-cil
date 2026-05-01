#include <stdio.h>
#include <string.h>

#include "../constants.h"
#include "../grammar_enum.h"
#include "../lexer/lexer.h"
#include "parser.h"

ast_node parse_variabel(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_VARIABEL_ERR, sizeof(result.error_msg)-1);

    token curr_token = scan_token(input);
    consume_next_if_current_string_match(&curr_token, NAMA, "variabel");
    consume_next_if_current_type_match(&curr_token, SPASI);
    consume_next_if_current_type_match(&curr_token, KATA_KUNCI_TIPE_DATA);
    consume_next_if_current_type_match(&curr_token, SPASI);
    if (curr_token.type != NAMA) {
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
        result.type = VARIABEL;
        result.next_input = curr_token.next;
        strncpy(result.error_msg, "\0", 1);
    }
    return result;
}

ast_node parse_konstanta(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_KONSTANTA_ERR, sizeof(result.error_msg)-1);

    token curr_token = scan_token(input);
    consume_next_if_current_string_match(&curr_token, NAMA, "konstanta");
    consume_next_if_current_type_match(&curr_token, SPASI);
    consume_next_if_current_type_match(&curr_token, KATA_KUNCI_TIPE_DATA);
    consume_next_if_current_type_match(&curr_token, SPASI);
    if (curr_token.type != NAMA) {
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
        result.next_input = curr_token.next;
        strncpy(result.error_msg, "\0", 1);
    }
    return result;
}

ast_node parse_ekspresi_aritmatika(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_EKSP_ARITMATIKA_ERR, sizeof(result.error_msg)-1);

    /*
     * Pseudo code:
     *
     * a = parse_istilah()
     * while True:
     *   if next token == "+":
     *     scan token
     *     b = parse_istilah()
     *     a = TAMBAH(a, b)
     *   else if next token == "-":
     *     scan token
     *     b = parse_istilah()
     *     a = KURANG(a, b)
     *   else:
     *     return a
     *
     */
    ast_node left_node_result = parse_istilah(input);
    for (int i = 0; i < MAX_ITERATION; i++) {
        ast_node curr_node;
        token curr_token = scan_token(left_node_result.next_input);
        if (curr_token.type != SIMBOL && 
                (*(curr_token.value) != '+' || *(curr_token.value) != '-')) {
            return result;
        }

        token space_token = scan_token(curr_token.next);
        if (space_token.type != SPASI) {
            return result;
        }

        ast_node right_node_result = parse_istilah(space_token.next);
        if (right_node_result.type == INVALID_EXPRESSION) {
            return result;
        }

        switch (*(curr_token.value)) {
            case '+':
                curr_node.type = TAMBAH;
                break;
            case '-':
                curr_node.type = KURANG;
                break;
        }
        curr_node.left = &left_node_result;
        curr_node.right = &right_node_result;
        curr_node.value[0] = curr_token;
        left_node_result = curr_node;
    }

    result = left_node_result;
    strncpy(result.error_msg, "\0", 1);
    return result;
}

ast_node parse_istilah(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_ISTILAH_ERR, sizeof(result.error_msg)-1);

    /*
     * Pseudo code:
     *
     * a = parse_faktor()
     * while True:
     *   if next token == "*":
     *     scan token
     *     b = parse_faktor()
     *     a = KALI(a, b)
     *   else if next token == "/":
     *     scan token
     *     b = parse_faktor()
     *     a = BAGI(a, b)
     *   else:
     *     return a
     *
     */
    ast_node left_node_result = parse_faktor(input);
    for (int i = 0; i < MAX_ITERATION; i++) {
        ast_node curr_node;
        token curr_token = scan_token(left_node_result.next_input);
        if (curr_token.type != SIMBOL && 
                (*(curr_token.value) != '*' || *(curr_token.value) != '/')) {
            return result;
        }

        token space_token = scan_token(curr_token.next);
        if (space_token.type != SPASI) {
            return result;
        }

        ast_node right_node_result = parse_faktor(space_token.next);
        if (right_node_result.type == INVALID_EXPRESSION) {
            return result;
        }

        switch (*(curr_token.value)) {
            case '*':
                curr_node.type = KALI;
                break;
            case '/':
                curr_node.type = BAGI;
                break;
        }
        curr_node.left = &left_node_result;
        curr_node.right = &right_node_result;
        curr_node.value[0] = curr_token;
        left_node_result = curr_node;
    }

    result = left_node_result;
    strncpy(result.error_msg, "\0", 1);
    return result;
}

ast_node parse_faktor(char *input) {
    ast_node result;
    result.type = INVALID_EXPRESSION;
    strncpy(result.error_msg, PARS_FAKTOR_ERR, sizeof(result.error_msg)-1);

    /* first case, "variabel" spasi nama */
    token curr_token = scan_token(input);
    consume_next_if_current_string_match(&curr_token, NAMA, "variabel");
    consume_next_if_current_type_match(&curr_token, SPASI);
    if (curr_token.type == NAMA) {
        result.type = FAKTOR;
        result.next_input = curr_token.next;
        result.value[0] = curr_token;
        strncpy(result.error_msg, "\0", 1);
        return result;
    }

    /* second case, angka_bulat. restart from first input */
    curr_token = scan_token(input);
    if (curr_token.type == ANGKA_BULAT) {
        result.type = FAKTOR;
        result.next_input = curr_token.next;
        result.value[0] = curr_token;
        strncpy(result.error_msg, "\0", 1);
        return result;
    }

    /* third case, ekspresi_aritmatika. restart from first input */
    /*
    curr_token = scan_token(input);
    if (curr_token.type == SIMBOL && curr_token.value == "(") {
        // TODO: call parse_ekspresi_aritmatika()
    }
    */

    /* forth case, negation. restart from first input */
    curr_token = scan_token(input);
    if (curr_token.type == SIMBOL && *(curr_token.value) == '~') {
        curr_token = scan_token(curr_token.next);
        if (curr_token.type != SIMBOL && *(curr_token.value) != '(') {
            return result;
        }

        ast_node temp_result = parse_faktor(curr_token.next);
        curr_token = scan_token(temp_result.next_input);
        if (curr_token.type != SIMBOL && *(curr_token.value) != ')') {
            return result;
        }

        result.type = NEGASI;
        result.next_input = temp_result.next_input;
        result.left = &temp_result;
        strncpy(result.error_msg, "\0", 1);
        return result;
    }

    return result;
}

