#include "tests.h"

size_t test_lnew(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 3;

    t_list  test1 = lnew(NULL);
    t_list  test1_truth = (t_list) {
        0,
        NULL,
        NULL,
        NULL,
        &lpush,
        &linsert,
        &lmap,
        &lmapi,
        &lforeach,
        &lforeachi,
        &ljoin,
        &lfold,
        &lfoldi,
        &lpop,
        &lshift,
        &lnext
    };

    if (memcmp(&test1, &test1_truth, sizeof(t_list)))
        failed("lnew(NULL)\n");
    else
    {
        success_count += 1;
        success("lnew(NULL)\n");
    }

    t_lst_test  test2_tmp3 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    t_lst_test  test2_tmp2 = (t_lst_test) {(t_pelem) {(t_pelem *)(&test2_tmp3), NULL}, 0xfeedbeef};
    t_lst_test  test2_tmp1 = (t_lst_test) {(t_pelem) {(t_pelem *)(&test2_tmp2), NULL}, 0xfeedbeef};

    t_list  test2 = lnew((t_elem *)(&test2_tmp1));
    t_list  test2_truth = lnew(NULL);
    test2_truth.len = 3;
    test2_truth.first = (t_elem *)(&test2_tmp1);
    test2_truth.last = (t_elem *)(&test2_tmp3);

    if (memcmp(&test2, &test2_truth, sizeof(t_list)))
        failed("lnew(&test2_tmp1)\n");
    else
    {
        success_count += 1;
        success("lnew(&test2_tmp1)\n");
    }

    t_lst_test  test2_tmp3_cmp = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    t_lst_test  test2_tmp2_cmp = (t_lst_test) {(t_pelem) {(t_pelem *)(&test2_tmp3), NULL}, 0xfeedbeef};
    t_lst_test  test2_tmp1_cmp = (t_lst_test) {(t_pelem) {(t_pelem *)(&test2_tmp2), NULL}, 0xfeedbeef};
    
    if (memcmp(&test2_tmp1, &test2_tmp1_cmp, sizeof(t_lst_test)) ||
        memcmp(&test2_tmp2, &test2_tmp2_cmp, sizeof(t_lst_test)) ||
        memcmp(&test2_tmp3, &test2_tmp3_cmp, sizeof(t_lst_test)))
        failed("memcmp on elements of created list\n");
    else
    {
        success_count += 1;
        success("memcmp on elements of created list\n");
    }

    return (success_count);
}

size_t test_lpnew(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 3;

    t_plist  test1 = lpnew(NULL);
    t_plist  test1_truth = (t_plist) {
        0,
        NULL,
        NULL,
        NULL,
        &lppush,
        &lpinsert,
        &lpmap,
        &lpmapi,
        &lpforeach,
        &lpforeachi,
        &lpjoin,
        &lpfold,
        &lpfoldi,
        &lppop,
        &lpshift,
        &lpnext,
        &lprevious
    };

    if (memcmp(&test1, &test1_truth, sizeof(t_plist)))
        failed("lpnew(NULL)\n");
    else
    {
        success_count += 1;
        success("lpnew(NULL)\n");
    }

    t_lst_test  test2_tmp3 = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    t_lst_test  test2_tmp2 = (t_lst_test) {(t_pelem) {(t_pelem *)(&test2_tmp3), NULL}, 0xfeedbeef};
    t_lst_test  test2_tmp1 = (t_lst_test) {(t_pelem) {(t_pelem *)(&test2_tmp2), NULL}, 0xfeedbeef};

    t_plist  test2 = lpnew((t_pelem *)(&test2_tmp1));
    t_plist  test2_truth = lpnew(NULL);
    test2_truth.len = 3;
    test2_truth.first = (t_pelem *)(&test2_tmp1);
    test2_truth.last = (t_pelem *)(&test2_tmp3);

    if (memcmp(&test2, &test2_truth, sizeof(t_plist)))
        failed("lpnew(&test2_tmp1)\n");
    else
    {
        success_count += 1;
        success("lpnew(&test2_tmp1)\n");
    }

    t_lst_test  test2_tmp3_cmp = (t_lst_test) {(t_pelem) {NULL, NULL}, 0xfeedbeef};
    t_lst_test  test2_tmp2_cmp = (t_lst_test) {(t_pelem) {(t_pelem *)(&test2_tmp3), NULL}, 0xfeedbeef};
    t_lst_test  test2_tmp1_cmp = (t_lst_test) {(t_pelem) {(t_pelem *)(&test2_tmp2), NULL}, 0xfeedbeef};

    test2_tmp3_cmp.listable.prev = (t_pelem *)&test2_tmp2;
    test2_tmp2_cmp.listable.prev = (t_pelem *)&test2_tmp1;
    
    if (memcmp(&test2_tmp1, &test2_tmp1_cmp, sizeof(t_lst_test)) ||
    memcmp(&test2_tmp2, &test2_tmp2_cmp, sizeof(t_lst_test)) ||
    memcmp(&test2_tmp3, &test2_tmp3_cmp, sizeof(t_lst_test)))
        failed("memcmp on elements of created plist (and relinking)\n");
    else
    {
        success_count += 1;
        success("memcmp on elements of created plist (and relinking)\n");
    }

    return (success_count);
}