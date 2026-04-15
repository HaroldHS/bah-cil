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
        case INVALID_TERMINAL:     return "INVALID";
        default:                   return "INVALID";
    }
}

const char* get_expression_name(EXPRESSION e) {
    switch (e) {
        case VARIABEL:           return "VARIABEL";
        case KONSTANTA:          return "KONSTANTA";
        case ARITMATIKA:         return "ARITMATIKA";
        case ISTILAH:            return "ISTILAH";
        case FAKTOR:             return "FAKTOR";
        case KONDISI:            return "KONDISI";
        case TAMPILKAN:          return "TAMPILKAN";
        case INVALID_EXPRESSION: return "INVALID";
        default:                 return "INVALID";
    }
}
