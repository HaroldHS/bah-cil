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
} token;

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

token scan_kata_kunci_tipe_data(char *input);

token scan_variabel(char *input);

token scan_konstanta(char *input);

#endif
