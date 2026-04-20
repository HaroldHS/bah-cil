#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../constants.h"
#include "lexer.h"

/*
 * scan_token() works by pattern matching given string via calling all scan_*()
 * methods one-by-one and return a `token` object.
 */
token scan_token(char *input) {
    token result;

    // Order of the pattern matching affects the token precedence
    result = scan_untaian(input); /* first '`' indicates string */
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_kata_kunci_tipe_data(input);
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_nama(input); /* precedence = NAMA first then KATA */
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_angka_bulat(input);
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_berhenti(input); /* first ';' labelled as BERHENTI, not SIMBOL */
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_alfabet(input);
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_angka(input);
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_simbol(input);
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_simbol_identasi(input);
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_spasi(input);
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_identasi(input);
    if (result.type != INVALID_TERMINAL) return result;

    result = scan_boolean(input);
    if (result.type != INVALID_TERMINAL) return result;

    return result; /* default fallback after last call still invalid */
}

/*
 * check_token_string() is the boilerplate for checking token literal in parser.c
 */
bool check_token_string(token *scanned_token, TERMINAL type, char *target) {
    if (scanned_token->type == type) {
        char var_word[scanned_token->length];
        sprintf(var_word, "%.*s", scanned_token->length, scanned_token->value);
        if (strncmp(var_word, target, strlen(target)) == 0) return true;
    }
    return false;
}

/*
 * consume_next_if_current_type_match() is the boilerplate for consuming & update 
 * given token to next token if the type is matched, otherwise just stay as it is 
 * (for parser.c)
 */
void consume_next_if_current_type_match(token *given, TERMINAL type) {
    if (given->type == type) {
        *given = scan_token(given->next);
    }
}

/*
 * consume_next_if_current_string_match() is the boilerplate for consuming & update 
 * given token to next token if the type & string are matched, otherwise just stay 
 * as it is (for parser.c)
 */
void consume_next_if_current_string_match(token *given, TERMINAL type, char *target) {
    if (given->type == type) {
        char var_word[given->length];
        sprintf(var_word, "%.*s", given->length, given->value);
        if (strncmp(var_word, target, strlen(target)) == 0) *given = scan_token(given->next);
    }
}

token scan_alfabet(char *input) {
    token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_ALFABET_ERR, sizeof(result.error_msg)-1);

    if (('A' <= input[0] && input[0] <= 'Z') || 
            ('a' <= input[0] && input[0] <= 'z')) {
        result.type = ALFABET;
        result.next++;
        result.length++;
        strncpy(result.error_msg, "\0", 1);
    }

    return result;
}

token scan_angka(char *input) {
    token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_ANGKA_ERR, sizeof(result.error_msg)-1);

    if ('0' <= input[0] && input[0] <= '9') {
        result.type = ANGKA;
        result.next++;
        result.length++;
        strncpy(result.error_msg, "\0", 1);
    }

    return result;
}

token scan_simbol(char *input) {
    token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_SIMBOL_ERR, sizeof(result.error_msg)-1);

    char list_of_symbols[23] = {
        '[', ']', '{', '}', '(', ')', '<', '>', '\'', '"',
        '=', '.', ',', ';', '+', '-', '*', '/', '\\', '?',
        '|', '&', '_'};
    for (int i=0; i<23; i++) {
        if (input[0] == list_of_symbols[i]) {
            result.type = SIMBOL;
            result.next++;
            result.length++;
            strncpy(result.error_msg, "\0", 1);
            break;
        }
    } /* iterate through list_of_symbols */
    return result;
}

token scan_simbol_identasi(char *input) {
    token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_SIMBOL_IDENTASI_ERR, sizeof(result.error_msg)-1);

    char list_of_identation_symbols[2] = {'\n', '\t'};
    for (int i=0; i<2; i++) {
        if (input[0] == list_of_identation_symbols[i]) {
            result.type = SIMBOL_IDENTASI;
            result.next++;
            result.length++;
            strncpy(result.error_msg, "\0", 1);
            break;
        }
    }
    return result;
}

token scan_spasi(char *input) {
    token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_SPASI_ERR, sizeof(result.error_msg)-1);

    if (input[0] == ' ') {
        result.type = SPASI;
        result.next++;
        result.length++;
        strncpy(result.error_msg, "\0", 1);
    }
    return result;
}

token scan_identasi(char *input) {
    token result;
    result.type = IDENTASI;
    result.value = input;
    result.next = input;
    result.length = 0;
    strncpy(result.error_msg, "\0", 1);

    for (int counter = 0; counter < MAX_ITERATION; counter++) {
        token simbol_identasi_token = scan_simbol_identasi(input);
        token spasi_token = scan_simbol_identasi(input);
        if (simbol_identasi_token.length != 0) {
            input += simbol_identasi_token.length;
            result.next += simbol_identasi_token.length;
            result.length += simbol_identasi_token.length;
        }
        if(spasi_token.length != 0) {
            input += spasi_token.length;
            result.next += spasi_token.length;
            result.length += spasi_token.length;
        }
        if ((simbol_identasi_token.length == 0) && (spasi_token.length == 0)) {
            break; /* stop if input is neither simbol_identasi nor spasi */
        }
    }
    return result;
}

token scan_berhenti(char *input) {
    token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_BERHENTI_ERR, sizeof(result.error_msg)-1);

    if (input[0] == ';') {
        result.type = BERHENTI;
        result.next++;
        result.length++;
        strncpy(result.error_msg, "\0", 1);
    }
    return result;
}

token scan_boolean(char *input) {
    token result;
    result.next = input;
    result.value = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_BOOLEAN_ERR, sizeof(result.error_msg)-1);

    char* benar = "benar";
    char* salah = "salah";
    bool is_benar_flag = true;
    bool is_salah_flag = true;

    if (strncmp(input, benar, 5) != 0) {
        is_benar_flag = false;
    }
    if (strncmp(input, salah, 5) != 0) {
        is_salah_flag = false;
    }

    if (is_benar_flag || is_salah_flag) {
        result.type = BOOLEAN;
        result.next += 5;
        result.length = 5;
        strncpy(result.error_msg, "\0", 1);
    }
    return result;
}

token scan_angka_bulat(char *input) {
    token result;
    result.next = input;
    result.value = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_ANGKA_BULAT_ERR, sizeof(result.error_msg)-1);

    bool first_angka_flag = false;
    if (input[0] == '-') {
        for (int counter = 0; counter < MAX_ITERATION; counter++) {
            token angka_token = scan_angka(++input);
            if (angka_token.type == ANGKA) {
                /* flag is used to call methods just one time (prevent excessive call)*/
                if (!first_angka_flag) {
                    strncpy(result.error_msg, "\0", 1);
                    result.type = ANGKA_BULAT;
                    first_angka_flag = true;
                    result.next++; /* +1 due to first encountered minus symbol*/
                    result.length++;
                }
                result.next++;
                result.length++;
                continue;
            }
            break;
        }
    } else {
        for (int counter = 0; counter < MAX_ITERATION; counter++) {
            token angka_token = scan_angka(input++);
            if (angka_token.type == ANGKA) {
                if (!first_angka_flag) {
                    strncpy(result.error_msg, "\0", 1);
                    result.type = ANGKA_BULAT;
                    first_angka_flag = true;
                }
                result.next++;
                result.length++;
                continue;
            }
            break;
        }
    } /* if negative number {...} else {-- handle positive number --} */
    return result;
}

token scan_untaian(char *input) {
    token result;
    result.next = input;
    result.value = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_UNTAIAN_ERR, sizeof(result.error_msg)-1);

    if (input[0] != '`') {
        return result;
    }

    for (int idx = 1; idx <= MAX_ITERATION; idx++) {
        if (input[idx] == '`') {
            result.type = UNTAIAN;
            result.next += idx + 1; /* +1 is added due to first backtick symbol */
            result.length += idx + 1;
            strncpy(result.error_msg, "\0", 1);
            break;
        }
    } /* starts from 1 to skip the first backtick symbol */

    return result;
}

token scan_nama(char *input) {
    token result;
    result.next = input;
    result.value = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_NAMA_ERR, sizeof(result.error_msg)-1);

    token nama = scan_alfabet(input);
    int counter;
    if (nama.type == ALFABET) {
        for (counter = 1; counter <= MAX_ITERATION; counter++) {
            nama = scan_alfabet(nama.next);
            if (nama.type == ALFABET) {
                continue;
            }
            nama = scan_angka(nama.next);
            if (nama.type == ANGKA) {
                continue;
            }
            nama = scan_simbol(nama.next);
            if (nama.type == SIMBOL && nama.value[0] == '_') {
                continue;
            }
            break;
        }

        result.type = NAMA;
        result.next += counter;
        result.length += counter;
        strncpy(result.error_msg, "\0", 1);
    }

    return result;
}

token scan_kata_kunci_tipe_data(char *input) {
    token result;
    result.next = input;
    result.value = input;
    result.length = 0;
    result.type = INVALID_TERMINAL;
    strncpy(result.error_msg, LEX_KATA_KUNCI_TIPE_DATA_ERR, sizeof(result.error_msg)-1);

    if (strncmp(input, "bilangan-bulat", 14) == 0) {
        result.type = KATA_KUNCI_TIPE_DATA;
        result.next += 14;
        result.length += 14;
        strncpy(result.error_msg, "\0", 1);
    }
    if ((strncmp(input, "boolean", 7) == 0) || 
            (strncmp(input, "untaian", 7) == 0)) {
        result.type = KATA_KUNCI_TIPE_DATA;
        result.next += 7;
        result.length += 7;
        strncpy(result.error_msg, "\0", 1);
    }

    return result;
}
