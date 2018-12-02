#include "tests.h"

size_t test_anew(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

	t_array	test = anew(NULL, 0, sizeof(int));
	t_array truth = (t_array) {0, 0, sizeof(int), NULL, NULL};

	*number_of_tests += 1;
    if (memcmp(&test, &truth, sizeof(t_array)))
        failed("anew(NULL, 0, int)\n");
    else
    {
        success_count += 1;
        success("anew(NULL, 0, int)\n");
    }

	test = anew(NULL, 10, sizeof(int));
	truth = (t_array) {10, sizeof(int) * 10, sizeof(int), test.mem, test.mem};

	*number_of_tests += 1;
    if (memcmp(&test, &truth, sizeof(t_array)) && test.mem != NULL)
        failed("anew(NULL, 10, int)\n");
    else
    {
        success_count += 1;
        success("anew(NULL, 10, int)\n");
    }

	int *test_array = malloc(sizeof(int) * 100);
	test = anew(test_array, 100, sizeof(int));
	truth = (t_array) {100, sizeof(int) * 100, sizeof(int), test_array, test_array};

	*number_of_tests += 1;
    if (memcmp(&test, &truth, sizeof(t_array)))
        failed("anew(int *, 100, int)\n");
    else
    {
        success_count += 1;
        success("anew(int *, 100, int)\n");
    }

	return (success_count);
}
