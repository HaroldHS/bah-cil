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
    INVALID
} TERMINAL;

typedef enum {
    KATA_KUNCI_TIPE_DATA,
    VARIABEL,
    KONSTANTA,
    EKSPRESI_ARITMATIKA,
    ISTILAH,
    FAKTOR,
    KONDISI,
    EKSPRESI_TAMPILKAN,
    PERNYATAAN,
    FUNGSI,
    KUMPULAN_PARAMETER,
    PARAMETER
} NONTERMINAL;

const char* get_terminal_name(TERMINAL t);

#endif
