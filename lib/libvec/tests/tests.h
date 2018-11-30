#ifndef TESTS_H
# define TESTS_H

# include "../includes/float_math.h"
# include "../includes/fixed_math.h"
# include "../includes/vec.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

//size_t test_fixed(size_t *number_of_tests);
size_t test_float(size_t *number_of_tests);
size_t test_vec(size_t *number_of_tests);

int		fc(float a, float b);
void    print_vec(t_vec3 vec);
void success(const char *str);
void failed(const char *str);

#endif
