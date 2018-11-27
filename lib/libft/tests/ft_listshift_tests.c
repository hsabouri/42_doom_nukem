#include "tests.h"

size_t test_lshift(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

    t_list test1 = lnew(NULL);

    *number_of_tests += 1;
    if (test1.shift(&test1) != NULL)
        failed("lshift of an empty list\n");
    else
    {
        success_count += 1;
        success("lshift of an empty list\n");
    }

    t_lst_test test_elem_to_insert1 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xdead10cc};
    test1.LPUSH(&test1, &test_elem_to_insert1);
    t_lst_test *res = (t_lst_test *)test1.shift(&test1);
    t_list truth = lnew(NULL);
    t_lst_test *test_elem_truth = &test_elem_to_insert1;

    *number_of_tests += 1;
    if (memcmp(&test1, &truth, sizeof(t_list)) || test_elem_truth != res)
    {
        failed("lshift an element from a list of len 1\n");
    }
    else
    {
        success_count += 1;
        success("lshift an element from a list of len 1\n");
    }

    test1 = lnew(NULL);
    t_lst_test test_elem_to_insert2 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xdead10cc};
    test1.LPUSH(&test1, &test_elem_to_insert1)->LPUSH(&test1, &test_elem_to_insert2);
    truth = lnew(NULL);
    truth.LPUSH(&truth, &test_elem_to_insert2);
    res = (t_lst_test *)test1.shift(&test1);
    test_elem_truth = &test_elem_to_insert1;

    *number_of_tests += 1;
    if (memcmp(&test1, &truth, sizeof(t_list)) || test_elem_truth != res)
        failed("lshift an element from a list of len 2\n");
    else
    {
        success_count += 1;
        success("lshift an element from a list of len 2\n");
    }

    return (success_count);
}

size_t test_lpshift(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

    t_plist test1 = lpnew(NULL);

    *number_of_tests += 1;
    if (test1.shift(&test1) != NULL)
        failed("lpshift of an empty list\n");
    else
    {
        success_count += 1;
        success("lpshift of an empty list\n");
    }

    t_lst_test test_elem_to_insert1 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xdead10cc};
    test1.LPPUSH(&test1, &test_elem_to_insert1);
    t_lst_test *res = (t_lst_test *)test1.shift(&test1);
    t_plist truth = lpnew(NULL);
    t_lst_test *test_elem_truth = &test_elem_to_insert1;

    *number_of_tests += 1;
    if (memcmp(&test1, &truth, sizeof(t_plist)) || test_elem_truth != res)
    {
        failed("lpshift an element from a list of len 1\n");
    }
    else
    {
        success_count += 1;
        success("lpshift an element from a list of len 1\n");
    }

    test1 = lpnew(NULL);
    t_lst_test test_elem_to_insert2 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xdead10cc};
    test1.LPPUSH(&test1, &test_elem_to_insert1)->LPPUSH(&test1, &test_elem_to_insert2);
    truth = lpnew(NULL);
    truth.LPPUSH(&truth, &test_elem_to_insert2);
    res = (t_lst_test *)test1.shift(&test1);
    test_elem_truth = &test_elem_to_insert1;

    *number_of_tests += 1;
    if (memcmp(&test1, &truth, sizeof(t_plist)) || test_elem_truth != res)
        failed("lpshift an element from a list of len 2\n");
    else
    {
        success_count += 1;
        success("lpshift an element from a list of len 2\n");
    }

    return (success_count);
}