#include "tests.h"

size_t test_lnext(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

    t_list test1 = lnew(NULL);
    t_elem  *res = test1.next(&test1);
    t_list test1_truth = lnew(NULL);
    t_elem *res_truth = NULL;

    *number_of_tests += 1;
    if (res_truth != res || memcmp(&test1, &test1_truth, sizeof(t_list)))
    {
        failed("lnext on empty list\n");
    }
    else
    {
        success("lnext on empty list\n");
        success_count += 1;
    }

    t_lst_test test_elem_to_insert1 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xdead10cc};
    test1.LPUSH(&test1, &test_elem_to_insert1);
    test1_truth = test1;
    test1_truth.current = (t_elem *)&test_elem_to_insert1;
    res = test1.next(&test1);
    res_truth = (t_elem *)&test_elem_to_insert1;

    *number_of_tests += 1;
    if (res_truth != res || memcmp(&test1, &test1_truth, sizeof(t_list)))
    {
        failed("lnext on list of len 1\n");
    }
    else
    {
        success("lnext on list of len 1\n");
        success_count += 1;
    }
   
    test1_truth = test1;
    test1_truth.current = NULL;
    res = test1.next(&test1);
    res_truth = NULL;

    *number_of_tests += 1;
    if (res_truth != res || memcmp(&test1, &test1_truth, sizeof(t_list)))
    {
        failed("lnext on list of len 1 (one more time)\n");
    }
    else
    {
        success("lnext on list of len 1 (one more time)\n");
        success_count += 1;
    }

    test1_truth = test1;
    test1_truth.current = NULL;
    res = test1.next(&test1);
    res_truth = NULL;

    *number_of_tests += 1;
    if (res_truth != res || memcmp(&test1, &test1_truth, sizeof(t_list)))
    {
        failed("lnext on list of len 1 (one more time)\n");
    }
    else
    {
        success("lnext on list of len 1 (one more time)\n");
        success_count += 1;
    }

    return (success_count);
}

size_t test_lpnext(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

    return (success_count);
}