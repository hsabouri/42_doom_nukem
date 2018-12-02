#include "tests.h"

size_t test_apop(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

	int *res = apop(NULL);

	*number_of_tests += 1;
	if (res != NULL)
        failed("apop(NULL)\n");
    else
    {
        success_count += 1;
        success("apop(NULL)\n");
    }

	t_array test = anew(NULL, 0, sizeof(int));
	t_array truth = test;
	res = apop(&test);

	*number_of_tests += 1;
	if (memcmp(&test, &truth, sizeof(t_array)) || res != NULL)
        failed("apop(empty)\n");
    else
    {
        success_count += 1;
        success("apop(empty)\n");
    }

	int *content = malloc(2 * sizeof(int));
	content[0] = 0xfeed;
	content[1] = 0xbeef;
	test = anew(content, 2, sizeof(int));
	truth = test;
	truth.len -= 1;
	res = apop(&test);

	*number_of_tests += 1;
	if (memcmp(&test, &truth, sizeof(t_array)) || res != &(content[1]))
        failed("apop(size 2)\n");
    else
    {
        success_count += 1;
        success("apop(size 2)\n");
    }

	truth.len -= 1;
	res = apop(&test);

	*number_of_tests += 1;
	if (memcmp(&test, &truth, sizeof(t_array)) || res != &(content[0]))
        failed("apop(size 1)\n");
    else
    {
        success_count += 1;
        success("apop(size 1)\n");
    }

	res = apop(&test);
	res = apop(&test);

	*number_of_tests += 1;
	if (memcmp(&test, &truth, sizeof(t_array)) || res != NULL)
        failed("apop(size 0)\n");
    else
    {
        success_count += 1;
        success("apop(size 0)\n");
    }

	return (success_count);
}
