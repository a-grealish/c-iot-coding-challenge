#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "check_file_parser.h"
#include "../src/file_parser.h"

START_TEST (testReverseStringToFloat_normal) {
    float test_val = 1.01;
    char input[] = "10.1";

    ck_assert(reverseStringToFloat(&input[0]) == test_val);
}
END_TEST

START_TEST (testReverseStringToFloat_negative) {
    float test_val = -1.01;
    char input[] = "10.1-";

    ck_assert(reverseStringToFloat(&input[0]) == test_val);
}
END_TEST

START_TEST (testReverseStringToFloat_newline) {
    float test_val = 1.01;
    char input[] = "\n10.1\n";

    ck_assert(reverseStringToFloat(&input[0]) == test_val);
}
END_TEST

START_TEST (testReverseStringToFloat_non_numeric) {
    // Will reverse the string and ignore chars after any
    // non-numerical char as standard atof
    float test_val = 1.0;
    char input[] = "1abc0.1";

    ck_assert(reverseStringToFloat(&input[0]) == test_val);
}
END_TEST

START_TEST (testReverseStringToFloat_no_number) {
    // Will reverse the string and ignore chars after any
    // non-numerical char as standard atof
    float test_val = 1.0;
    char input[] = "abcde";

    printf("%f \n", reverseStringToFloat(&input[0]));

    ck_assert(reverseStringToFloat(&input[0]) == test_val);
}
END_TEST


Suite * FileParserSuite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("FileParser");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, testReverseStringToFloat_normal);
    tcase_add_test(tc_core, testReverseStringToFloat_negative);
    tcase_add_test(tc_core, testReverseStringToFloat_newline);
    tcase_add_test(tc_core, testReverseStringToFloat_non_numeric);
    tcase_add_test(tc_core, testReverseStringToFloat_no_number);
    suite_add_tcase(s, tc_core);

    return s;
}

