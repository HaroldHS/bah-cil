#ifndef grammar_enum_h
#define grammar_enum_h

typedef enum {
    ALFABET,
    ANGKA,
    SIMBOL,
    SIMBOL_IDENTASI,
    SPASI,
    IDENTASI,
    BERHENTI,
    BOOLEAN,
    ANGKA_BULAT,
    UNTAIAN,
    NAMA,
    KATA_KUNCI_TIPE_DATA,
    INVALID_TERMINAL
} TERMINAL;

typedef enum {
    VARIABEL,
    KONSTANTA,
    ARITMATIKA,
    ISTILAH,
    FAKTOR,
    KONDISI,
    TAMPILKAN,
    INVALID_EXPRESSION
} EXPRESSION;

const char* get_terminal_name(TERMINAL t);
const char* get_expression_name(EXPRESSION e);

#endif
