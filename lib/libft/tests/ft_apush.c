#include "tests.h"

size_t test_apush(size_t *number_of_tests)
{
    size_t  success_count = 0;

    *number_of_tests = 0;

	t_array	*res = apush(NULL, NULL);

	*number_of_tests += 1;
	if (res != NULL)
        failed("apush(NULL, NULL)\n");
    else
    {
        success_count += 1;
        success("apush(NULL, NULL)\n");
    }

	int *content = malloc(2 * sizeof(int));
	content[0] = 0xfeed;
	content[1] = 0xbeef;
	t_array array = anew(content, 2, sizeof(int));
	int	yolo = 0xfeed;
	apush(&array, &yolo);

	*number_of_tests += 1;
	if (content == array.mem || ((int *)array.mem)[0] != 0xfeed || ((int *)array.mem)[1] != 0xbeef || ((int *)array.mem)[2] != 0xfeed)
        failed("apush(array, 0xfeed) array of len 2\n");
    else
    {
        success_count += 1;
        success("apush(array, 0xfeed) array of len 2\n");
    }

	array.len -= 1;
	yolo = 0xbee;
	content = (int *)array.mem;
	apush(&array, &yolo);
	
	*number_of_tests += 1;
	if (content != array.mem || ((int *)array.mem)[0] != 0xfeed || ((int *)array.mem)[1] != 0xbeef || ((int *)array.mem)[2] != 0xbee)
		failed("apush(array, 0xbee) array of len 2 with enough room at the end\n");
	else
	{
		success_count += 1;
		success("apush(array, 0xbee) array of len 2 with enough room at the end\n");
	}

	array.len -= 1;
	array.first += sizeof(int);
	content = array.mem;
	apush(&array, &yolo);

	*number_of_tests += 1;
	if (content != array.mem || array.mem != array.first || ((int *)array.mem)[0] != 0xbeef || ((int *)array.mem)[1] != 0xbee || ((int *)array.mem)[2] != 0xbee)
	{
		failed("apush(array, 0xbee) array of len 2 with enough room at the beginning\n");
		printf("array.mem: %zu -> %zu\n", (size_t)content, (size_t)array.mem);
		printf("array.first: %zu -> %zu\n", (size_t)array.mem, (size_t)array.first);
		printf("array[0]: %d -> %d\n", 0xbeef, ((int *)array.mem)[0]);
		printf("array[1]: %d -> %d\n", 0xbee, ((int *)array.mem)[1]);
		printf("array[2]: %d -> %d\n", 0xbee, ((int *)array.mem)[2]);
	}
	else
	{
		success_count += 1;
		success("apush(array, 0xbee) array of len 2 with enough room at the beginning\n");
	}

	return (success_count);
}
