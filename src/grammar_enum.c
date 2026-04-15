#include "grammar_enum.h"

const char* get_terminal_name(TERMINAL t) {
    switch (t) {
        case ALFABET:              return "ALFABET";
        case ANGKA:                return "ANGKA";
        case SIMBOL:               return "SIMBOL";
        case SIMBOL_IDENTASI:      return "SIMBOL_IDENTASI";
        case SPASI:                return "SPASI";
        case BERHENTI:             return "BERHENTI";
        case BOOLEAN:              return "BOOLEAN";
        case ANGKA_BULAT:          return "ANGKA_BULAT";
        case UNTAIAN:              return "UNTAIAN";
        case NAMA:                 return "NAMA";
        case KATA_KUNCI_TIPE_DATA: return "KATA_KUNCI_TIPE_DATA";
        case INVALID:              return "INVALID";
        default:                   return "INVALID";
    }
}
