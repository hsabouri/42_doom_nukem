#include "tests.h"

size_t test_linsert(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

    t_list  test1 = lnew(NULL);
    t_lst_test test_elem_to_insert1 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1.insert(&test1, (t_elem*) &test_elem_to_insert1);
    t_list  test1_truth = lnew(NULL);
    test1_truth.len = 1;
    test1_truth.first = (t_elem *)&test_elem_to_insert1;
    test1_truth.last = (t_elem *)&test_elem_to_insert1;
    test1_truth.current = NULL;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
        failed("linsert(elem) in an empty list\n");
    else
    {
        success_count += 1;
        success("linsert(elem) in an empty list\n");
    }

    test1 = lnew(NULL);
    t_lst_test test_elem_to_insert2 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test_elem_to_insert1 = (t_lst_test) {(t_pelem) {(t_pelem *)&test_elem_to_insert2, NULL}, 0xfeedbeef};
    test1.insert(&test1, (t_elem*) &test_elem_to_insert1);
    test1_truth.len = 2;
    test1_truth.first = (t_elem *)&test_elem_to_insert1;
    test1_truth.last = (t_elem *)&test_elem_to_insert2;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
        failed("linsert(list) in an empty list\n");
    else
    {
        success_count += 1;
        success("linsert(list) in an empty list\n");
    }

    
    t_lst_test test_elem_to_insert3 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1.insert(&test1, (t_elem *)&test_elem_to_insert3);
    test1_truth.len = 3;
    test1_truth.first = (t_elem *)&test_elem_to_insert3;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
        failed("linsert(elem) in a list\n");
    else
    {
        success_count += 1;
        success("linsert(elem) in a list\n");
    }
    
    t_lst_test test_elem_to_insert4 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1.insert(&test1, (t_elem *)& test_elem_to_insert4);
    test1_truth.len = 4;
    test1_truth.first = (t_elem *)&test_elem_to_insert4;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
        failed("linsert(elem) in a list\n");
    else
    {
        success_count += 1;
        success("linsert(elem) in a list\n");
    }

    test1.insert(&test1, NULL);

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
        failed("linsert(NULL) in a list\n");
    else
    {
        success_count += 1;
        success("linsert(NULL) in a list\n");
    }

    *number_of_tests += 1;

    if (test_elem_to_insert1.listable.next == (t_pelem *)&test_elem_to_insert2
        && test_elem_to_insert2.listable.next == NULL
        && test_elem_to_insert3.listable.next == (t_pelem *)&test_elem_to_insert1
        && test_elem_to_insert4.listable.next == (t_pelem *)&test_elem_to_insert3)
    {
        success_count += 1;
        success("list linking tests\n");
    }
    else
        failed("list linking tests\n");



    return (success_count);
}

size_t test_lpinsert(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

    t_plist  test1 = lpnew(NULL);
    t_lst_test test_elem_to_insert1 = (t_lst_test) {(t_pelem) {NULL, NULL},
        0xfeedbeef};
    test1.insert(&test1, (t_pelem*)&test_elem_to_insert1);
    t_plist  test1_truth = lpnew(NULL);
    test1_truth.len = 1;
    test1_truth.first = (t_pelem *)&test_elem_to_insert1;
    test1_truth.last = (t_pelem *)&test_elem_to_insert1;
    test1_truth.current = NULL;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
        failed("lpinsert(elem) in an empty list\n");
    else
    {
        success_count += 1;
        success("lpinsert(elem) in an empty list\n");
    }

    test1 = lpnew(NULL);
    t_lst_test test_elem_to_insert2 = (t_lst_test) {(t_pelem) {NULL, NULL},
        0xfeedbeef};
    test_elem_to_insert1 = (t_lst_test) {(t_pelem) {
        (t_pelem *)&test_elem_to_insert2, NULL}, 0xfeedbeef};
    test_elem_to_insert2.listable.prev = (t_pelem *)&test_elem_to_insert1;
    test1.insert(&test1, (t_pelem*) &test_elem_to_insert1);
    test1_truth.len = 2;
    test1_truth.first = (t_pelem *)&test_elem_to_insert1;
    test1_truth.last = (t_pelem *)&test_elem_to_insert2;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
        failed("lpinsert(list) in an empty list\n");
    else
    {
        success_count += 1;
        success("lpinsert(list) in an empty list\n");
    }
    
    t_lst_test test_elem_to_insert3 = (t_lst_test) {(t_pelem) {NULL, NULL},
        0xfeedbeef};
    test1.insert(&test1, (t_pelem *)& test_elem_to_insert3);
    test1_truth.len = 3;
    test1_truth.first = (t_pelem *)&test_elem_to_insert3;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
        failed("lpinsert(elem) in a list\n");
    else
    {
        success_count += 1;
        success("lpinsert(elem) in a list\n");
    }
    
    t_lst_test test_elem_to_insert4 = (t_lst_test) {(t_pelem) {NULL, NULL},
        0xfeedbeef};
    test1.insert(&test1, (t_pelem *)&test_elem_to_insert4);
    test1_truth.len = 4;
    test1_truth.first = (t_pelem *)&test_elem_to_insert4;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
        failed("lpinsert(elem) in a list\n");
    else
    {
        success_count += 1;
        success("lpinsert(elem) in a list\n");
    }

    test1.insert(&test1, NULL);

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
        failed("lpinsert(NULL) in a list\n");
    else
    {
        success_count += 1;
        success("lpinsert(NULL) in a list\n");
    }

    *number_of_tests += 1;

    if (test_elem_to_insert1.listable.next == (t_pelem *)&test_elem_to_insert2
        && test_elem_to_insert2.listable.next == NULL
        && test_elem_to_insert3.listable.next == (t_pelem *)&test_elem_to_insert1
        && test_elem_to_insert4.listable.next == (t_pelem *)&test_elem_to_insert3
        && test_elem_to_insert1.listable.prev == (t_pelem *)&test_elem_to_insert3
        && test_elem_to_insert4.listable.prev == NULL
        && test_elem_to_insert3.listable.prev == (t_pelem *)&test_elem_to_insert4
        && test_elem_to_insert2.listable.prev == (t_pelem *)&test_elem_to_insert1)
    {
        success_count += 1;
        success("list linking tests\n");
    }
    else
        failed("list linking tests\n");

    return (success_count);
}