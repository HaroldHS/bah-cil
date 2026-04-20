#include <stdio.h>

#include "grammar_enum.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int main() {
    /* Parser example*/
    char *expr_input_1 = "variabel bilangan-bulat test = 123;";
    ast_node expr_result_1 = parse_variabel(expr_input_1);
    printf("Input to parse: %s\n", expr_input_1);
    printf("Expression type: %s\n", get_expression_name(expr_result_1.type));
    printf("Expression error message: %s\n\n", expr_result_1.error_msg);

    char *expr_input_2 = "variabel random test = 123;";
    ast_node expr_result_2 = parse_variabel(expr_input_2);
    printf("Input to parse: %s\n", expr_input_2);
    printf("Expression type: %s\n", get_expression_name(expr_result_2.type));
    printf("Expression error message: %s\n\n", expr_result_2.error_msg);

    char *expr_input_3 = "konstanta bilangan-bulat test = 123;";
    ast_node expr_result_3 = parse_konstanta(expr_input_3);
    printf("Input to parse: %s\n", expr_input_3);
    printf("Expression type: %s\n", get_expression_name(expr_result_3.type));
    printf("Expression error message: %s\n\n", expr_result_3.error_msg);

    return 0;
}
