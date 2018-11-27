#ifndef TESTS_H
# define TESTS_H

# include "../includes/libft.h"
# include <stdio.h>

typedef struct  s_lst_test {
    t_pelem     listable;
    size_t      magic1;
}               t_lst_test;

size_t test_lnew(size_t *number_of_tests);
size_t test_lpnew(size_t *number_of_tests);
size_t test_lpush(size_t *number_of_tests);
size_t test_lppush(size_t *number_of_tests);
size_t test_linsert(size_t *number_of_tests);
size_t test_lpinsert(size_t *number_of_tests);
size_t test_ljoin(size_t *number_of_tests);
size_t test_lpjoin(size_t *number_of_tests);
size_t test_lshift(size_t *number_of_tests);
size_t test_lpshift(size_t *number_of_tests);
size_t test_lnext(size_t *number_of_tests);
size_t test_lpnext(size_t *number_of_tests);

void show_list(t_list list);
void show_plist(t_plist list);
void success(const char *str);
void failed(const char *str);

#endif
