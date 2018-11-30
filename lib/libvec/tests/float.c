#include "tests.h"

size_t	test_float(size_t *number_of_tests)
{
	size_t	success_count = 0;

	*number_of_tests = 0;

	float test = 10.0;
	float sq = fast_sqrt(test);
	float truth = sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_sqrt()\n");
	}
	else
		failed("fast_sqrt()\n");

	test = 100;
	sq = fast_sqrt(test);
	truth = sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_sqrt()\n");
	}
	else
		failed("fast_sqrt()\n");

	test = 1000;
	sq = fast_sqrt(test);
	truth = sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_sqrt()\n");
	}
	else
		failed("fast_sqrt()\n");

	test = 10000;
	sq = fast_sqrt(test);
	truth = sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_sqrt()\n");
	}
	else
		failed("fast_sqrt()\n");

	test = 874839746346;
	sq = fast_sqrt(test);
	truth = sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_sqrt()\n");
	}
	else
		failed("fast_sqrt()\n");

	test = 0.0237034659898275;
	sq = fast_sqrt(test);
	truth = sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_sqrt()\n");
	}
	else
		failed("fast_sqrt()\n");

	test = 2;
	sq = fast_sqrt(test);
	truth = sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_sqrt()\n");
	}
	else
		failed("fast_sqrt()\n");

	test = 0.0000023452;
	sq = fast_sqrt(test);
	truth = sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_sqrt()\n");
	}
	else
		failed("fast_sqrt()\n");

	test = 100;
	sq = fast_inv_sqrt(test);
	truth = 1 / sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_inv_sqrt()\n");
	}
	else
		failed("fast_inv_sqrt()\n");

	test = 1000;
	sq = fast_inv_sqrt(test);
	truth = 1 / sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_inv_sqrt()\n");
	}
	else
		failed("fast_inv_sqrt()\n");

	test = 10000;
	sq = fast_inv_sqrt(test);
	truth = 1 / sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_inv_sqrt()\n");
	}
	else
		failed("fast_inv_sqrt()\n");

	test = 874839746346;
	sq = fast_inv_sqrt(test);
	truth = 1 / sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_inv_sqrt()\n");
	}
	else
		failed("fast_inv_sqrt()\n");

	test = 0.0237034659898275;
	sq = fast_inv_sqrt(test);
	truth = 1 / sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_inv_sqrt()\n");
	}
	else
		failed("fast_inv_sqrt()\n");

	test = 2;
	sq = fast_inv_sqrt(test);
	truth = 1 / sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_inv_sqrt()\n");
	}
	else
		failed("fast_inv_sqrt()\n");

	test = 0.0000023452;
	sq = fast_inv_sqrt(test);
	truth = 1 / sqrtf(test);

	*number_of_tests += 1;
	if (fc(sq, truth))
	{
		success_count += 1;
		success("fast_inv_sqrt()\n");
	}
	else
		failed("fast_inv_sqrt()\n");

	return (success_count);
}
