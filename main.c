#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "learquivo.h"

void test_leLinha_reads_line_correctly(void)
{
    ArqCmds ac = fopen("test_input.txt", "r");
    char *buf = NULL;
    int bufLen = 0;

    CU_ASSERT(leLinha(ac, &buf, &bufLen) == true);
    CU_ASSERT_STRING_EQUAL(buf, "This is a test line.");
    CU_ASSERT(bufLen == 5);

    fclose(ac);
    free(buf);
}

void test_leLinha_checks_null_buffer(void)
{
    ArqCmds ac = fopen("test_input.txt", "r");
    char* initialBuf = malloc(sizeof(char));
    int initialBufLen = 0;

    CU_ASSERT(leLinha(ac, &initialBuf, &initialBufLen) == true);
    CU_ASSERT(initialBuf != NULL);
    
    // set buffer to null and check if it's still null
    initialBuf = NULL;
    CU_ASSERT(leLinha(ac, &initialBuf, &initialBufLen) == true);
    CU_ASSERT(initialBuf == NULL);
    
    fclose(ac);
}

void test_leLinha_checks_length_after_parsing(void)
{
    ArqCmds ac = fopen("test_input.txt", "r");
    char *buf = malloc(100*sizeof(char));
    int bufLen = 0;

    CU_ASSERT(leLinha(ac, &buf, &bufLen) == true);
    CU_ASSERT_STRING_EQUAL(buf, "This is a test line.");
    CU_ASSERT(bufLen == 5);

    fclose(ac);
    free(buf);
}

void test_leLinha_reads_zero_length_string(void)
{
    ArqCmds ac = fopen("test_input.txt", "r");
    char* initialBuf = malloc(sizeof(char));
    int initialBufLen = 0;
    char emptyLine[300] = "";

    CU_ASSERT(leLinha(ac, &initialBuf, &initialBufLen) == true);

    // Check if it correctly reads an empty string
    fscanf(ac, "%299[^\n]", emptyLine);
    fgetc(ac);
    CU_ASSERT_STRING_EQUAL(initialBuf, emptyLine);

    free(initialBuf);
    fclose(ac);
}

void test_leLinha_returns_false_when_no_more_data_to_be_read(void)
{
    ArqCmds ac = fopen("test_input.txt", "r");
    char *buf = NULL;
    int bufLen = 0;

    // read all lines to end of file
    while (leLinha(ac, &buf, &bufLen))
    {
        free(buf);
        buf = NULL;
        bufLen = 0;
    }

    // check that it returns false at the end of the file
    CU_ASSERT(leLinha(ac, &buf, &bufLen) == false);

    fclose(ac);
}

int main()
{
    CU_pSuite suite = NULL;

    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    // Add a suite to the registry
    suite = CU_add_suite("leLinha_tests", NULL, NULL);
    if (NULL == suite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if ((NULL == CU_add_test(suite, "test_leLinha_reads_line_correctly", test_leLinha_reads_line_correctly)) ||
        (NULL == CU_add_test(suite, "test_leLinha_checks_null_buffer", test_leLinha_checks_null_buffer)) ||
        (NULL == CU_add_test(suite, "test_leLinha_checks_length_after_parsing", test_leLinha_checks_length_after_parsing)) ||
        (NULL == CU_add_test(suite, "test_leLinha_reads_zero_length_string", test_leLinha_reads_zero_length_string)) ||
        (NULL == CU_add_test(suite, "test_leLinha_returns_false_when_no_more_data_to_be_read", test_leLinha_returns_false_when_no_more_data_to_be_read)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE); // VERBOSE = show details
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
