#include <stdio.h>

#include "grammar_enum.h"
#include "lexer/lexer.h"

int main() {
    char *test1 = "hello";
    terminal_token result1 = scan_token(test1);
    printf("Terminal token: %s\n", result1.value);
    printf("Terminal token type: %s\n", get_terminal_name(result1.type));
    printf("Terminal token error message: %s\n", result1.error_msg);
    printf("Next string: %s\n", result1.next);

    char *test2 = "hello 123";
    terminal_token result2 = scan_token(test2);
    printf("Terminal token: %s\n", result2.value);
    printf("Terminal token type: %s\n", get_terminal_name(result2.type));
    printf("Terminal token error message: %s\n", result2.error_msg);
    printf("Next string: %s\n", result2.next);

    return 0;
}
