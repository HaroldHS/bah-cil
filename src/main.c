#include <stdio.h>

#include "grammar_enum.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int main() {
    /* Lexer / Tokenizer example */
    char *test1 = "bilangan-bulat -123 `test`;";
    token result1 = scan_token(test1);
    printf("Terminal token: %s\n", result1.value);
    printf("Terminal token type: %s\n", get_terminal_name(result1.type));
    printf("Terminal token value: %.*s\n", result1.length, result1.value);
    printf("Terminal token error message: %s\n", result1.error_msg);
    printf("Next string: %s\n\n", result1.next);

    token result2 = scan_token(result1.next);
    printf("Terminal token: %s\n", result2.value);
    printf("Terminal token type: %s\n", get_terminal_name(result2.type));
    printf("Terminal token value: %.*s\n", result2.length, result2.value);
    printf("Terminal token error message: %s\n", result2.error_msg);
    printf("Next string: %s\n\n", result2.next);

    token result3 = scan_token(result2.next);
    printf("Terminal token: %s\n", result3.value);
    printf("Terminal token type: %s\n", get_terminal_name(result3.type));
    printf("Terminal token value: %.*s\n", result3.length, result3.value);
    printf("Terminal token error message: %s\n", result3.error_msg);
    printf("Next string: %s\n\n", result3.next);

    token result4 = scan_token(result3.next);
    printf("Terminal token: %s\n", result4.value);
    printf("Terminal token type: %s\n", get_terminal_name(result4.type));
    printf("Terminal token value: %.*s\n", result4.length, result4.value);
    printf("Terminal token error message: %s\n", result4.error_msg);
    printf("Next string: %s\n\n", result4.next);

    token result5 = scan_token(result4.next);
    printf("Terminal token: %s\n", result5.value);
    printf("Terminal token type: %s\n", get_terminal_name(result5.type));
    printf("Terminal token value: %.*s\n", result5.length, result5.value);
    printf("Terminal token error message: %s\n", result5.error_msg);
    printf("Next string: %s\n\n", result5.next);

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
    ast_node expr_result_3 = parse_constant(expr_input_3);
    printf("Input to parse: %s\n", expr_input_3);
    printf("Expression type: %s\n", get_expression_name(expr_result_3.type));
    printf("Expression error message: %s\n\n", expr_result_3.error_msg);

    return 0;
}
