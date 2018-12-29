#include "tests.h"

/*
t_fixed Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return (f_from_float(y));
}

size_t	test_fixed(size_t *number_of_tests)
{
	size_t	success_count = 0;

	*number_of_tests = 0;

	t_fixed a = f_from_int(10);
	t_fixed truth = 163840;

	*number_of_tests += 1;
	if (memcmp(&a, &truth, sizeof(t_fixed)))
		failed("t_fixed a = 10\n");
	else
	{
		success_count += 1;
		success("t_fixed a = 10\n");
	}

	a = f_from_int(-10);
	truth = -163840;

	*number_of_tests += 1;
	if (memcmp(&a, &truth, sizeof(t_fixed)))
		failed("t_fixed a = -10\n");
	else
	{
		success_count += 1;
		success("t_fixed a = -10\n");
	}

	a = f_from_int(0);
	truth = 0;

	*number_of_tests += 1;
	if (memcmp(&a, &truth, sizeof(t_fixed)))
		failed("t_fixed a = 0\n");
	else
	{
		success_count += 1;
		success("t_fixed a = 0\n");
	}

	t_fixed b = f_from_int(20);
	truth = 327680;

	*number_of_tests += 1;
	if (memcmp(&b, &truth, sizeof(t_fixed)))
		failed("t_fixed b = 20\n");
	else
	{
		success_count += 1;
		success("t_fixed b = 20\n");
	}

	a = f_from_int(10);
	t_fixed c = a + b;
	truth = 327680 + 163840;

	*number_of_tests += 1;
	if (memcmp(&c, &truth, sizeof(t_fixed)))
		failed("t_fixed c = a + b\n");
	else
	{
		success_count += 1;
		success("t_fixed c = a + b\n");
	}

	c = f_mul(a, b);
	truth = 3276800;

	*number_of_tests += 1;
	if (memcmp(&c, &truth, sizeof(t_fixed)))
		failed("t_fixed c = a * b\n");
	else
	{
		success_count += 1;
		success("t_fixed c = a * b\n");
	}

	c = f_div(a, b);
	truth = 8192;

	*number_of_tests += 1;
	if (memcmp(&c, &truth, sizeof(t_fixed)))
		failed("t_fixed c = a / b\n");
	else
	{
		success_count += 1;
		success("t_fixed c = a / b\n");
	}

	c = a * 20;
	truth = 3276800;

	*number_of_tests += 1;
	if (memcmp(&c, &truth, sizeof(t_fixed)))
		failed("t_fixed c = a * (int)b\n");
	else
	{
		success_count += 1;
		success("t_fixed c = a * (int)b\n");
	}

	c = a / 20;
	truth = 8192;

	*number_of_tests += 1;
	if (memcmp(&c, &truth, sizeof(t_fixed)))
		failed("t_fixed c = a / (int)b\n");
	else
	{
		success_count += 1;
		success("t_fixed c = a / (int)b\n");
	}

	a = f_from_int(10);
	c = f_mul(a, c);
	truth = f_from_int(5);

	*number_of_tests += 1;
	if (memcmp(&c, &truth, sizeof(t_fixed)))
		failed("t_fixed c = a / 0.5\n");
	else
	{
		success_count += 1;
		success("t_fixed c = a / 0.5\n");
	}

	c = f_from_float(0.5);
	truth = 8192;

	*number_of_tests += 1;
	if (memcmp(&c, &truth, sizeof(t_fixed)))
		failed("t_fixed c = 0.5\n");
	else
	{
		success_count += 1;
		success("t_fixed c = 0.5\n");
	}

	c = f_from_float(-0.5);
	truth = -8192;

	*number_of_tests += 1;
	if (memcmp(&c, &truth, sizeof(t_fixed)))
		failed("t_fixed c = -0.5\n");
	else
	{
		success_count += 1;
		success("t_fixed c = -0.5\n");
	}

	printf("REAL: %d\nMINE: %d\n\n", Q_rsqrt(10000), f_inv_sqrt(f_from_int(10000)));

	return (success_count);
}
*/