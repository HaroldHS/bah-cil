#include <stdio.h>

#include "grammar_enum.h"
#include "lexer/lexer.h"

int main() {
    char *test1 = "bilangan-bulat -123;";
    terminal_token result1 = scan_token(test1);
    printf("Terminal token: %s\n", result1.value);
    printf("Terminal token type: %s\n", get_terminal_name(result1.type));
    printf("Terminal token value: %.*s\n", result1.length, result1.value);
    printf("Terminal token error message: %s\n", result1.error_msg);
    printf("Next string: %s\n\n", result1.next);

    terminal_token result2 = scan_token(result1.next);
    printf("Terminal token: %s\n", result2.value);
    printf("Terminal token type: %s\n", get_terminal_name(result2.type));
    printf("Terminal token value: %.*s\n", result2.length, result2.value);
    printf("Terminal token error message: %s\n", result2.error_msg);
    printf("Next string: %s\n\n", result2.next);

    terminal_token result3 = scan_token(result2.next);
    printf("Terminal token: %s\n", result3.value);
    printf("Terminal token type: %s\n", get_terminal_name(result3.type));
    printf("Terminal token value: %.*s\n", result3.length, result3.value);
    printf("Terminal token error message: %s\n", result3.error_msg);
    printf("Next string: %s\n\n", result3.next);

    terminal_token result4 = scan_token(result3.next);
    printf("Terminal token: %s\n", result4.value);
    printf("Terminal token type: %s\n", get_terminal_name(result4.type));
    printf("Terminal token value: %.*s\n", result4.length, result4.value);
    printf("Terminal token error message: %s\n", result4.error_msg);
    printf("Next string: %s\n\n", result4.next);

    return 0;
}
