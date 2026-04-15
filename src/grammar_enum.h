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
    INVALID,
} TERMINAL;

const char* get_terminal_name(TERMINAL t);

#endif
