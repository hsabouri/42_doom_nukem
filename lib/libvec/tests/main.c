#include "tests.h"

void success(const char *str)
{
	printf("\x1b[32mUNIT TEST SUCCESS\x1b[0m: %s", str);
}

void failed(const char *str)
{
	printf("\x1b[31mUNIT TEST FAILED\x1b[0m: %s", str);
}

int		fc(float a, float b)
{
	const float b_div = b / 100;

	if (b > 0.00001)
		if (a <= b + b_div && a >= b - b_div)
			return 1;
		else
			return 0;
	else if (b < -0.00001)
		if (a >= b + b_div && a <= b - b_div)
			return 1;
		else
			return 0;
	else
		if (a < 0.0001 && a > -0.0001)
			return 1;
		else
			return 0;
}

void    print_vec(t_vec3 vec)
{
	printf("vec {\n	x: %f,\n	y: %f,\n	z: %f,\n	s: %f\n}\n\n", vec.x, vec.y, vec.z, vec.s);
}

int main(void)
{
	size_t number_of_tests = 0;
	size_t total = 0;
	size_t success_count = 0;
	
	//success_count += test_fixed(&number_of_tests);
	//total += number_of_tests;
	success_count += test_float(&number_of_tests);
	total += number_of_tests;
	success_count += test_vec(&number_of_tests);
	total += number_of_tests;
	
	printf("\n%zu / %zu unit tests succeeded\n", success_count, total);

	if (total != success_count)
	{
		printf("\x1b[31mUNIT TESTS FAILED !!!\x1b[0m\n");
		return (1);
	}
	else
	{
		printf("\x1b[32mUNIT TESTS SUCCEEDED !!!\x1b[0m\n");
		return (0);
	}
}
