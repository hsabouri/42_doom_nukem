#include "tests.h"

size_t test_ashift(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

	int *res = ashift(NULL);

	*number_of_tests += 1;
	if (res != NULL)
        failed("ashift(NULL)\n");
    else
    {
        success_count += 1;
        success("ashift(NULL)\n");
    }

	t_array test = anew(NULL, 0, sizeof(int));
	t_array truth = test;
	res = ashift(&test);

	*number_of_tests += 1;
	if (memcmp(&test, &truth, sizeof(t_array)) || res != NULL)
        failed("ashift(empty)\n");
    else
    {
        success_count += 1;
        success("ashift(empty)\n");
    }

	int *content = malloc(2 * sizeof(int));
	content[0] = 0xfeed;
	content[1] = 0xbeef;
	test = anew(content, 2, sizeof(int));
	truth = test;
	truth.len -= 1;
	truth.first += sizeof(int);
	res = ashift(&test);

	*number_of_tests += 1;
	if (memcmp(&test, &truth, sizeof(t_array)) || res != &(content[0]))
        failed("ashift(size 2)\n");
    else
    {
        success_count += 1;
        success("ashift(size 2)\n");
    }

	truth.len--;
	truth.first = truth.mem;
	res = ashift(&test);

	*number_of_tests += 1;
	if (memcmp(&test, &truth, sizeof(t_array)) || res != &(content[1]))
        failed("ashift(size 1)\n");
    else
    {
        success_count += 1;
        success("ashift(size 1)\n");
    }

	truth.len = 0;
	truth.first = truth.mem;
	res = ashift(&test);

	*number_of_tests += 1;
	if (memcmp(&test, &truth, sizeof(t_array)) || res != NULL)
        failed("ashift(size 0)\n");
    else
    {
        success_count += 1;
        success("ashift(size 0)\n");
    }

	return (success_count);
}
