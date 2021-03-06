#include <check.h>
#include <stdlib.h>
#include <stdio.h>

// Pull in the test suites 
#include "check_file_parser.h"
#include "check_cluster.h"

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;
    
    s = FileParserSuite();
    sr = srunner_create(s);
    srunner_add_suite(sr, ClusterSuite());
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}