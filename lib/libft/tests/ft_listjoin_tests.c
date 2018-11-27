#include "tests.h"

size_t test_ljoin(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

    t_list  test1 = lnew(NULL);
    t_list  test2 = lnew(NULL);
    test1.join(&test1, &test2);
    t_list  test_truth = lnew(NULL);

    *number_of_tests += 1;
    if (memcmp(&test1, &test_truth, sizeof(t_list)))
        failed("ljoin(empty, empty) joining two empty lists\n");
    else
    {
        success_count += 1;
        success("ljoin(empty, empty) joining two empty lists\n");
    }

    t_lst_test test_elem_to_insert1 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1 = lnew((t_elem *)&test_elem_to_insert1);
    test2 = lnew(NULL);
    test_truth = test1;
    test1.join(&test1, &test2);

    *number_of_tests += 1;
    if (memcmp(&test1, &test_truth, sizeof(t_list)))
    {
        failed("ljoin(list, empty) joining an empty list to a list. GOT:\n");
        show_list(test1);
        printf("\nEXPECTED: ");
        show_list(test_truth);
    }
    else
    {
        success_count += 1;
        success("ljoin(list, empty) joining an empty list to a list\n");
    }

    t_lst_test test_elem_to_insert3 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    t_lst_test test_elem_to_insert2 = (t_lst_test) {(t_pelem) {(t_pelem *)&test_elem_to_insert3, NULL}, 0xfeedbeef};
    test2 = lnew((t_elem *)&test_elem_to_insert2);

    test1 = lnew((t_elem *)&test_elem_to_insert1);
    test1.join(&test1, &test2);
    test_truth = lnew(NULL);
    test_truth.len = 3;
    test_truth.first = (t_elem *)&test_elem_to_insert1;
    test_truth.last = (t_elem *)&test_elem_to_insert3;

    *number_of_tests += 1;
    if (memcmp(&test1, &test_truth, sizeof(t_list)))
        failed("ljoin(list, list) joining two lists\n");
    else
    {
        success_count += 1;
        success("ljoin(list, list) joining two lists\n");
    }

    test2 = test1;
    test2.len = 10;
    test_truth = test2;
    test1.join(&test1, &test2);

    *number_of_tests += 1;
    if (memcmp(&test1, &test_truth, sizeof(t_list)))
        failed("ljoin(list, list) joining two identic lists with artificially different len\n");
    else
    {
        success_count += 1;
        success("ljoin(list, list) joining two identic lists with artificially different len\n");
    }

    *number_of_tests += 1;
    if (test_elem_to_insert1.listable.next == (t_pelem *)&test_elem_to_insert2)
    {
        success_count += 1;
        success("ljoin(list, list) linking test\n");
    }
    else
        success("ljoin(list, list) linking test\n");

    return (success_count);
}

size_t test_lpjoin(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

    t_plist  test1 = lpnew(NULL);
    t_plist  test2 = lpnew(NULL);
    test1.join(&test1, &test2);
    t_plist  test_truth = lpnew(NULL);

    *number_of_tests += 1;
    if (memcmp(&test1, &test_truth, sizeof(t_plist)))
        failed("lpjoin(empty, empty) joining two empty lists\n");
    else
    {
        success_count += 1;
        success("lpjoin(empty, empty) joining two empty lists\n");
    }

    t_lst_test test_elem_to_insert1 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1 = lpnew((t_pelem *)&test_elem_to_insert1);
    test_truth = test1;
    test1.join(&test1, &test2);

    *number_of_tests += 1;
    if (memcmp(&test1, &test_truth, sizeof(t_plist)))
        failed("lpjoin(list, empty) joining an empty list to a list\n");
    else
    {
        success_count += 1;
        success("lpjoin(list, empty) joining an empty list to a list\n");
    }

    t_lst_test test_elem_to_insert3 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    t_lst_test test_elem_to_insert2 = (t_lst_test) {(t_pelem) {(t_pelem *)&test_elem_to_insert3, NULL}, 0xfeedbeef};
    test2 = lpnew((t_pelem *)&test_elem_to_insert2);

    test1.join(&test1, &test2);
    test_truth = lpnew(NULL);
    test_truth.len = 3;
    test_truth.first = (t_pelem *)&test_elem_to_insert1;
    test_truth.last = (t_pelem *)&test_elem_to_insert3;

    *number_of_tests += 1;
    if (memcmp(&test1, &test_truth, sizeof(t_plist)))
        failed("lpjoin(list, list) joining two lists\n");
    else
    {
        success_count += 1;
        success("lpjoin(list, list) joining two lists\n");
    }
 
    test2 = test1;
    test2.len = 10;
    test_truth = test2;
    test1.join(&test1, &test2);

    *number_of_tests += 1;
    if (memcmp(&test1, &test_truth, sizeof(t_plist)))
        failed("ljoin(list, list) joining two identic lists with artificially different len\n");
    else
    {
        success_count += 1;
        success("ljoin(list, list) joining two identic lists with artificially different len\n");
    }   

    *number_of_tests += 1;
    if (test_elem_to_insert1.listable.next == (t_pelem *)&test_elem_to_insert2 &&
    test_elem_to_insert2.listable.prev == (t_pelem *)&test_elem_to_insert1)
    {
        success_count += 1;
        success("lpjoin(list, list) linking test\n");
    }
    else
        success("lpjoin(list, list) linking test\n");

    return (success_count);
}