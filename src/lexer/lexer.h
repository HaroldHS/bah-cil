#ifndef lexer_h
#define lexer_h

#include "../constants.h"
#include "../grammar_enum.h"

typedef struct {
    TERMINAL type;
    char     *value;
    char     *next;
    int      length;
    char     error_msg[ERR_MSG_MAX_LEN];
} terminal_token;

terminal_token scan_token(char *input);

terminal_token scan_alfabet(char *input);

terminal_token scan_angka(char *input);

terminal_token scan_simbol(char *input);

terminal_token scan_simbol_identasi(char *input);

terminal_token scan_spasi(char *input);

terminal_token scan_identasi(char *input);

terminal_token scan_berhenti(char *input);

terminal_token scan_boolean(char *input);

terminal_token scan_angka_bulat(char *input);

terminal_token scan_untaian(char *input);

terminal_token scan_name(char *input);

terminal_token scan_kata_kunci_tipe_data(char *input);

terminal_token scan_variabel(char *input);

terminal_token scan_konstanta(char *input);

#endif
