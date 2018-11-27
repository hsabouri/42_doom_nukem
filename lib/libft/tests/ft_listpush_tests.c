#include "tests.h"

size_t test_lpush(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

    t_list  test1 = lnew(NULL);
    t_lst_test test_elem_to_push1 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1.push(&test1, (t_elem*) &test_elem_to_push1);
    t_list  test1_truth = lnew(NULL);
    test1_truth.len = 1;
    test1_truth.first = (t_elem *)&test_elem_to_push1;
    test1_truth.last = (t_elem *)&test_elem_to_push1;
    test1_truth.current = NULL;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
    {
        failed("lpush(elem) in an empty list\nGOT:");
        show_list(test1);
        printf("EXPECTED:");
        show_list(test1_truth);
    }
    else
    {
        success_count += 1;
        success("lpush(elem) in an empty list\n");
    }

    test1 = lnew(NULL);
    t_lst_test test_elem_to_push2 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test_elem_to_push1 = (t_lst_test) {(t_pelem) {(t_pelem *)&test_elem_to_push2, NULL}, 0xfeedbeef};
    test1.push(&test1, (t_elem*) &test_elem_to_push1);
    test1_truth.len = 2;
    test1_truth.first = (t_elem *)&test_elem_to_push1;
    test1_truth.last = (t_elem *)&test_elem_to_push2;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
    {
        failed("lpush(list) in an empty list\nGOT:");
        show_list(test1);
        printf("EXPECTED:");
        show_list(test1_truth);
    }
    else
    {
        success_count += 1;
        success("lpush(list) in an empty list\n");
    }

    
    t_lst_test test_elem_to_push3 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1.push(&test1, (t_elem *)& test_elem_to_push3);
    test1_truth.len = 3;
    test1_truth.last = (t_elem *)&test_elem_to_push3;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
    {
        failed("lpush(elem) in a list\nGOT:");
        show_list(test1);
        printf("EXPECTED:");
        show_list(test1_truth);
    }
    else
    {
        success_count += 1;
        success("lpush(elem) in a list\n");
    }
    
    t_lst_test test_elem_to_push4 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1.push(&test1, (t_elem *)& test_elem_to_push4);
    test1_truth.len = 4;
    test1_truth.last = (t_elem *)&test_elem_to_push4;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
    {
        failed("lpush(elem) in a list\nGOT:");
        show_list(test1);
        printf("EXPECTED:");
        show_list(test1_truth);
    }
    else
    {
        success_count += 1;
        success("lpush(elem) in a list\n");
    }

    test1.push(&test1, NULL);

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
    {
        failed("lpush(NULL) in a list\nGOT:");
        show_list(test1);
        printf("EXPECTED:");
        show_list(test1_truth);
    }
    else
    {
        success_count += 1;
        success("lpush(NULL) in a list\n");
    }

    *number_of_tests += 1;

    if (test_elem_to_push1.listable.next == (t_pelem *)&test_elem_to_push2 &&
    test_elem_to_push2.listable.next == (t_pelem *)&test_elem_to_push3 &&
    test_elem_to_push3.listable.next == (t_pelem *)&test_elem_to_push4 &&
    test_elem_to_push4.listable.next == NULL)
    {
        success_count += 1;
        success("list linking tests\n");
    }
    else
    {
        failed("list linking tests\nGOT:");
        show_list(test1);
        printf("EXPECTED:");
        show_list(test1_truth);
    }



    return (success_count);
}

size_t test_lppush(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

    t_plist  test1 = lpnew(NULL);
    t_lst_test test_elem_to_push1 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1.push(&test1, (t_pelem*) &test_elem_to_push1);
    t_plist  test1_truth = lpnew(NULL);
    test1_truth.len = 1;
    test1_truth.first = (t_pelem *)&test_elem_to_push1;
    test1_truth.last = (t_pelem *)&test_elem_to_push1;
    test1_truth.current = NULL;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
    {
        failed("lppush(elem) in an empty list\nGOT:");
        show_plist(test1);
        printf("EXPECTED:");
        show_plist(test1_truth);
    }
    else
    {
        success_count += 1;
        success("lppush(elem) in an empty list\n");
    }

    test1 = lpnew(NULL);
    t_lst_test test_elem_to_push2 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test_elem_to_push1 = (t_lst_test) {(t_pelem) {(t_pelem *)&test_elem_to_push2, NULL}, 0xfeedbeef};
    test_elem_to_push2.listable.prev = (t_pelem *)&test_elem_to_push1;
    test1.push(&test1, (t_pelem*)&test_elem_to_push1);
    test1_truth.len = 2;
    test1_truth.first = (t_pelem *)&test_elem_to_push1;
    test1_truth.last = (t_pelem *)&test_elem_to_push2;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
    {
        failed("lppush(list) in an empty list\nGOT:");
        show_plist(test1);
        printf("EXPECTED:");
        show_plist(test1_truth);
    }
    else
    {
        success_count += 1;
        success("lppush(list) in an empty list\n");
    }
    
    t_lst_test test_elem_to_push3 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1.push(&test1, (t_pelem *)&test_elem_to_push3);
    test1_truth.len = 3;
    test1_truth.last = (t_pelem *)&test_elem_to_push3;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
    {
        failed("lppush(elem) in a list\nGOT:");
        show_plist(test1);
        printf("EXPECTED:");
        show_plist(test1_truth);
    }
    else
    {
        success_count += 1;
        success("lppush(elem) in a list\n");
    }
    
    t_lst_test test_elem_to_push4 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    test1.push(&test1, (t_pelem *)&test_elem_to_push4);
    test1_truth.len = 4;
    test1_truth.last = (t_pelem *)&test_elem_to_push4;

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
    {
        failed("lppush(elem) in a list\nGOT:");
        show_plist(test1);
        printf("EXPECTED:");
        show_plist(test1_truth);
    }
    else
    {
        success_count += 1;
        success("lppush(elem) in a list\n");
    }

    test1.push(&test1, NULL);

    *number_of_tests += 1;
    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
    {
        failed("lppush(NULL) in a list\nGOT:");
        show_plist(test1);
        printf("EXPECTED:");
        show_plist(test1_truth);
    }
    else
    {
        success_count += 1;
        success("lppush(NULL) in a list\n");
    }

    *number_of_tests += 1;

    if (test_elem_to_push1.listable.next == (t_pelem *)&test_elem_to_push2 &&
    test_elem_to_push2.listable.next == (t_pelem *)&test_elem_to_push3 &&
    test_elem_to_push3.listable.next == (t_pelem *)&test_elem_to_push4 &&
    test_elem_to_push4.listable.next == NULL &&
    test_elem_to_push1.listable.prev == NULL &&
    test_elem_to_push4.listable.prev == (t_pelem *)&test_elem_to_push3 &&
    test_elem_to_push3.listable.prev == (t_pelem *)&test_elem_to_push2 &&
    test_elem_to_push2.listable.prev == (t_pelem *)&test_elem_to_push1)
    {
        success_count += 1;
        success("list linking tests\n");
    }
    else
    {
        failed("list linking tests\nGOT:");
        printf("\n 0x%04lx\n 0x%04lx\n 0x%04lx\n 0x%04lx\n 0x%04lx\n 0x%04lx\n 0x%04lx\n 0x%04lx\n\
EXPECTED:\n 0x%04lx\n 0x%04lx\n 0x%04lx\n 0x%04lx\n 0x%04lx\n 0x%04lx\n 0x%04lx\n 0x%04lx\n",
            (size_t)test_elem_to_push1.listable.next,
            (size_t)test_elem_to_push1.listable.prev,
            (size_t)test_elem_to_push2.listable.next,
            (size_t)test_elem_to_push2.listable.prev,
            (size_t)test_elem_to_push3.listable.next,
            (size_t)test_elem_to_push3.listable.prev,
            (size_t)test_elem_to_push4.listable.next,
            (size_t)test_elem_to_push4.listable.prev,
            (size_t)&test_elem_to_push2,
            (size_t)0,
            (size_t)&test_elem_to_push3,
            (size_t)&test_elem_to_push1,
            (size_t)&test_elem_to_push4,
            (size_t)&test_elem_to_push2,
            (size_t)0,
            (size_t)&test_elem_to_push3
        );
    }

    return (success_count);
}