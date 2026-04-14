#include <stdbool.h>
#include <string.h>

#include "../constants.h"
#include "lexer.h"

terminal_token scan_alfabet(char *input) {
    terminal_token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID;
    strncpy(result.error_msg, LEX_ALFABET_ERR, sizeof(result.error_msg)-1);

    int idx = 0;
    bool is_alfabet = false;
    for(;;) {
        if ((65 <= input[idx] && input[idx] <= 90) || (97 <= input[idx] && input[idx] <= 122)) {
            if (!is_alfabet) is_alfabet = true; /* set detection flag for the first time */
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

terminal_token scan_angka(char *input) {
    terminal_token result;
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

terminal_token scan_simbol(char *input) {
    terminal_token result;
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

terminal_token scan_simbol_identasi(char *input) {
    terminal_token result;
    result.value = input;
    result.next = input;
    result.length = 0;
    result.type = INVALID;
    strncpy(result.error_msg, LEX_SIMBOL_IDENTASI_ERR, sizeof(result.error_msg)-1);

    char list_of_identation_symbols[3] = {'\n', '\t', '\r'};
    for (int i=0; i<3; i++) {
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

terminal_token scan_spasi(char *input) {
    terminal_token result;
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

terminal_token scan_identasi(char *input) {
    terminal_token result;
    result.type = IDENTASI;
    result.value = input;
    result.next = input;
    result.length = 0;
    strncpy(result.error_msg, "\0", 1);

    for (;;) {
        terminal_token simbol_identasi_token = scan_simbol_identasi(input);
        terminal_token spasi_token = scan_simbol_identasi(input);
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

terminal_token scan_berhenti(char *input) {
    terminal_token result;
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

terminal_token scan_boolean(char *input) {
    terminal_token result;
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
        result.value = input;
        result.next += 5;
        result.length = 5;
        strncpy(result.error_msg, "\0", 1);
    }
    return result;
}

terminal_token scan_angka_bulat(char *input) {
    terminal_token result;
    result.next = input;
    result.value = input;
    result.length = 0;
    result.type = INVALID;
    strncpy(result.error_msg, LEX_ANGKA_BULAT_ERR, sizeof(result.error_msg)-1);

    if (input[0] == '-') {
        terminal_token simbol_identasi_token = scan_simbol_identasi(++input);
        if (simbol_identasi_token.length != 0) {
            result.type = ANGKA_BULAT;
            result.next += simbol_identasi_token.length;
            result.length += simbol_identasi_token.length;
            strncpy(result.error_msg, "\0", 1);
        }
    } else {
        terminal_token simbol_identasi_token = scan_simbol_identasi(++input);
        if (simbol_identasi_token.length != 0) {
            result.type = ANGKA_BULAT;
            result.next += simbol_identasi_token.length;
            result.length += simbol_identasi_token.length;
            strncpy(result.error_msg, "\0", 1);
        }
    }
    return result;
}
