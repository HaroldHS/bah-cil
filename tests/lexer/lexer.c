#include <assert.h>
#include <stdio.h>

#include "../../src/lexer/lexer.h"

void test_positive_case_boolean() {
    token test_1 = scan_token("benar");
    assert(test_1.type == BOOLEAN);
    token test_2 = scan_token("salah");
    assert(test_2.type == BOOLEAN);
    printf("[+] test_positive_case_boolean\n");
}

void test_positive_case_angka_bulat() {
    token test_1 = scan_token("1234");
    assert(test_1.type == ANGKA_BULAT);
    token test_2 = scan_token("-1234");
    assert(test_2.type == ANGKA_BULAT);
    printf("[+] test_positive_case_angka_bulat\n");
}

void test_positive_case_untaian() {
    token test_1 = scan_token("`Hello World`");
    assert(test_1.type == UNTAIAN);
    printf("[+] test_positive_case_untaian\n");
}

void test_positive_case_kata_kunci_tipe_data() {
    token test_1 = scan_token("bilangan-bulat");
    assert(test_1.type == KATA_KUNCI_TIPE_DATA);
    token test_2 = scan_token("boolean");
    assert(test_2.type == KATA_KUNCI_TIPE_DATA);
    token test_3 = scan_token("untaian");
    assert(test_3.type == KATA_KUNCI_TIPE_DATA);
    printf("[+] test_positive_case_kata_kunci_tipe_data\n");
}

void test_positive_case_nama() {
    token test_1 = scan_token("test");
    assert(test_1.type == NAMA);
    token test_2 = scan_token("test123");
    assert(test_2.type == NAMA);
    token test_3 = scan_token("test_123");
    assert(test_3.type == NAMA);
    printf("[+] test_positive_case_nama\n");
}

void test_combination() {
    token test = scan_token("bilangan-bulat -123 `test`;");
    assert(test.type == KATA_KUNCI_TIPE_DATA);
    consume_next_if_current_type_match(&test, KATA_KUNCI_TIPE_DATA);
    assert(test.type == SPASI);
    consume_next_if_current_type_match(&test, SPASI);
    assert(test.type == ANGKA_BULAT);
    consume_next_if_current_type_match(&test, ANGKA_BULAT);
    assert(test.type == SPASI);
    consume_next_if_current_type_match(&test, SPASI);
    assert(test.type == UNTAIAN);
    consume_next_if_current_type_match(&test, UNTAIAN);
    assert(test.type == BERHENTI);
    printf("[+] test_combination\n");
}
