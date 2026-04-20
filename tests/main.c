#include "./lexer/lexer.h"

int main() {
    test_positive_case_boolean();
    test_positive_case_angka_bulat();
    test_positive_case_untaian();
    test_positive_case_kata_kunci_tipe_data();
    test_positive_case_nama();
    test_combination();
    return 0;
}
