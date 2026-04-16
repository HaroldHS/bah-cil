#ifndef constants_h
#define constants_h

#define ERR_MSG_MAX_LEN           200
#define MAX_ITERATION             1024
#define MAX_TOKEN_IN_ONE_AST_NODE 10

/*
 * Error constants for lexer / tokenizer
 */
#define LEX_ALFABET_ERR              "failed to scan alphabet"
#define LEX_ANGKA_ERR                "failed to scan digit"
#define LEX_SIMBOL_ERR               "failed to scan symbol"
#define LEX_SIMBOL_IDENTASI_ERR      "failed to scan identation symbol"
#define LEX_SPASI_ERR                "failed to scan space character"
#define LEX_IDENTASI_ERR             "failed to scan identation"
#define LEX_BERHENTI_ERR             "failed to scan separator"
#define LEX_BOOLEAN_ERR              "failed to scan boolean"
#define LEX_ANGKA_BULAT_ERR          "failed to scan integer"
#define LEX_UNTAIAN_ERR              "failed to scan string"
#define LEX_NAMA_ERR                 "failed to scan name"
#define LEX_KATA_KUNCI_TIPE_DATA_ERR "failed to scan keyword"

/*
 * Error constants for parser
 */
#define PARS_VARIABEL_ERR  "failed to parse variable"
#define PARS_KONSTANTA_ERR "failed to parse constant"

/*
 * Macro to stringify string constants to obtain the constant name
 */
#define STRINGIFY(x) #x

#endif
