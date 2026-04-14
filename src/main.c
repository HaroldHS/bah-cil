#include <stdio.h>

#include "lexer/lexer.h"

int main() {
    char *test1 = "hello";
    terminal_token result1 = scan_alfabet(test1);
    printf("Terminal token: %s\n", result1.value);
    printf("Terminal token error message: %s\n", result1.error_msg);
    printf("Next string: %s\n", result1.next);

    char *test2 = "hello 123";
    terminal_token result2 = scan_angka(test2);
    printf("Terminal token: %s\n", result2.value);
    printf("Terminal token error message: %s\n", result2.error_msg);
    printf("Next string: %s\n", result2.next);

    return 0;
}
