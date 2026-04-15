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

    // TODO: Reorder the pattern matching as it affect the token precedence
    result = scan_kata_kunci_tipe_data(input);
    if (result.type != INVALID) return result;

    //result = scan_nama(input);
    //if (result.type != INVALID) return result;

    result = scan_angka_bulat(input);
    if (result.type != INVALID) return result;

    result = scan_berhenti(input); /* first ';' labelled as BERHENTI, not SIMBOL */
    if (result.type != INVALID) return result;

    result = scan_alfabet(input);
    if (result.type != INVALID) return result;

    result = scan_angka(input);
    if (result.type != INVALID) return result;

    result = scan_simbol(input);
    if (result.type != INVALID) return result;

    result = scan_simbol_identasi(input);
    if (result.type != INVALID) return result;

    result = scan_spasi(input);
    if (result.type != INVALID) return result;

    result = scan_identasi(input);
    if (result.type != INVALID) return result;

    result = scan_boolean(input);
    if (result.type != INVALID) return result;

    return result; /* default fallback after last call still invalid */
}

token scan_alfabet(char *input) {
    token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID;
    strncpy(result.error_msg, STRINGIFY(LEX_ALFABET_ERR), sizeof(result.error_msg)-1);

    int idx = 0;
    bool is_alfabet = false;
    for(;;) {
        if ((65 <= input[idx] && input[idx] <= 90) || 
                (97 <= input[idx] && input[idx] <= 122)) {
            if (!is_alfabet) is_alfabet = true; /* set flag only at first time */
            result.next++;
            result.length++;
            idx++;
            continue;
        } /* 'A' <= input <= 'Z' || 'a' <= input <= 'z' */
        break;
    }

    if (is_alfabet) {
        result.type = ALFABET;
        strncpy(result.error_msg, "\0", 1);
    }
    return result;
}

token scan_angka(char *input) {
    token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID;
    strncpy(result.error_msg, LEX_ANGKA_ERR, sizeof(result.error_msg)-1);

    int idx = 0;
    bool is_angka = false;
    for(;;) {
        if (48 <= input[idx] && input[idx] <= 57) {
            if (!is_angka) is_angka = true;
            result.next++;
            result.length++;
            idx++;
            continue;
        } /* '0' <= input <= '9' */
        break;
    }

    if (is_angka) {
        result.type = ANGKA;
        strncpy(result.error_msg, "\0", 1);
    }
    return result;
}

token scan_simbol(char *input) {
    token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID;
    strncpy(result.error_msg, LEX_SIMBOL_ERR, sizeof(result.error_msg)-1);

    char list_of_symbols[22] = {
        '[', ']', '{', '}', '(', ')', '<', '>', '\'', '"',
        '.', ',', ';', '+', '-', '*', '/', '\\', '?', '|',
        '&', '_'};
    for (int i=0; i<22; i++) {
        if (input[0] == list_of_symbols[i]) {
            result.type = SIMBOL;
            result.next++;
            result.length++;
            strncpy(result.error_msg, "\0", 1);
            break;
        }
    } /* iterate through list_of_symbols, 22 = length of list_of_symbols */
    return result;
}

token scan_simbol_identasi(char *input) {
    token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID;
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
    result.type = INVALID;
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

    for (;;) {
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
    result.type = INVALID;
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
    result.type = INVALID;
    strncpy(result.error_msg, LEX_BOOLEAN_ERR, sizeof(result.error_msg)-1);

    char* benar = "benar";
    char* salah = "salah";
    bool is_benar_flag = true;
    bool is_salah_flag = true;

    for (int i=0; i<5; i++) {
        if ((input[i] != benar[i]) && is_benar_flag) {
            is_benar_flag = false;
        }
        if ((input[i] != salah[i]) && is_salah_flag) {
            is_salah_flag = false;
        }
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
    result.type = INVALID;
    strncpy(result.error_msg, LEX_ANGKA_BULAT_ERR, sizeof(result.error_msg)-1);

    if (input[0] == '-') {
        token angka_token = scan_angka(++input);
        if (angka_token.type == ANGKA) {
            result.type = ANGKA_BULAT;
            result.next += angka_token.length + 1; /* +1 due to minus symbol */
            result.length += angka_token.length + 1;
            strncpy(result.error_msg, "\0", 1);
        }
    } else {
        token angka_token = scan_angka(input);
        if (angka_token.type == ANGKA) {
            result.type = ANGKA_BULAT;
            result.next += angka_token.length;
            result.length += angka_token.length;
            strncpy(result.error_msg, "\0", 1);
        }
    } /* if negative number {...} else {-- handle positive number --} */
    return result;
}

token scan_nama(char *input) {
    token result;
    return result;
}

token scan_untaian(char *input) {
    token result;
    return result;
}

token scan_kata_kunci_tipe_data(char *input) {
    token result;
    result.next = input;
    result.value = input;
    result.length = 0;
    result.type = INVALID;
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
