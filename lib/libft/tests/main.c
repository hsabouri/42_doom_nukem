#include "tests.h"

void show_list(t_list list)
{
    printf("{\n len: %zu,\n first: 0x%04lx,\n last: 0x%04lx,\n current: 0x%04lx\n}\n",
        (size_t)list.len,
        (size_t)list.first,
        (size_t)list.last,
        (size_t)list.current
    );
}

void show_plist(t_plist list)
{
    printf("{\n len: %zu,\n first: 0x%04lx,\n last: 0x%04lx,\n current: 0x%04lx\n}\n",
        (size_t)list.len,
        (size_t)list.first,
        (size_t)list.last,
        (size_t)list.current
    );
}

void success(const char *str)
{
    printf("\x1b[32mUNIT TEST SUCCESS\x1b[0m: %s", str);
}

void failed(const char *str)
{
    printf("\x1b[31mUNIT TEST FAILED\x1b[0m: %s", str);
}

int main(void)
{
    size_t number_of_tests = 0;
    size_t total = 0;
    size_t success_count = 0;
    
    success_count += test_lnew(&number_of_tests);
    total += number_of_tests;
    success_count += test_lpnew(&number_of_tests);
    total += number_of_tests;
    success_count += test_lpush(&number_of_tests);
    total += number_of_tests;
    success_count += test_lppush(&number_of_tests);
    total += number_of_tests;
    success_count += test_linsert(&number_of_tests);
    total += number_of_tests;
    success_count += test_lpinsert(&number_of_tests);
    total += number_of_tests;
    success_count += test_ljoin(&number_of_tests);
    total += number_of_tests;
    success_count += test_lpjoin(&number_of_tests);
    total += number_of_tests;
    success_count += test_lshift(&number_of_tests);
    total += number_of_tests;
    success_count += test_lpshift(&number_of_tests);
    total += number_of_tests;
    success_count += test_lnext(&number_of_tests);
    total += number_of_tests;
    
    printf("\n%zu / %zu unit tests succeeded\n", success_count, total);

    if (total != success_count)
    {
        printf("\x1b[31mUNIT TESTS FAILED !!!\x1b[0m\n");
        return (1);
    }
    else
    {
        printf("\x1b[32mUNIT TESTS SUCCEEDED !!!\x1b[0m\n");
        return (0);
    }
}