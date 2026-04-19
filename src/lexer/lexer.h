#ifndef lexer_h
#define lexer_h

#include <stdbool.h>

#include "../constants.h"
#include "../grammar_enum.h"

typedef struct {
    TERMINAL type;
    char     *value;
    char     *next;
    int      length;
    char     error_msg[ERR_MSG_MAX_LEN];
} token;

bool check_token_string(token *scanned_token, TERMINAL type, char *target);

void consume_next_if_current_type_match(token *given, TERMINAL type);

void consume_next_if_current_string_match(token *given, TERMINAL type, char *target);

token scan_token(char *input);

token scan_alfabet(char *input);

token scan_angka(char *input);

token scan_simbol(char *input);

token scan_simbol_identasi(char *input);

token scan_spasi(char *input);

token scan_identasi(char *input);

token scan_berhenti(char *input);

token scan_boolean(char *input);

token scan_angka_bulat(char *input);

token scan_untaian(char *input);

token scan_nama(char *input);

token scan_kata(char *input);

token scan_kata_kunci_tipe_data(char *input);

token scan_variabel(char *input);

token scan_konstanta(char *input);

#endif
