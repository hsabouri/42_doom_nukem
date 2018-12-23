#include "tests.h"

size_t	test_vec(size_t *number_of_tests)
{
	size_t	success_count = 0;

	*number_of_tests = 0;

	t_vec3	vec = vec3_new(100, 100, 100);
	t_vec3	truth = (t_vec3) {100, 100, 100};

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec_new(100, 100, 100)\n");
	}
	else
		failed("vec_new(100, 100, 100)\n");

	vec = vec3_new(235.928385, -0.134, 23.98385);
	truth = (t_vec3) {235.928385, -0.134, 23.98385};

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec_new(235.928385, -0.134, 23.98385)\n");
	}
	else
	{
		failed("vec_new(235.928385, -0.134, 23.98385)\n");
		print_vec(vec);
		print_vec(truth);
	}

	vec = vec3_new(0, 0, 0);
	truth = (t_vec3) {0, 0, 0};

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec_new(0, 0, 0)\n");
	}
	else
	{
		failed("vec_new(0, 0, 0)\n");
		print_vec(vec);
		print_vec(truth);
	}

	float dot = vec3_dot(vec3_new(3, -6, 4.5), vec3_new(-8.42362, 5, 2.3982835));
	float dot_truth = -44.47858425;

	*number_of_tests += 1;
	if (fc(dot, dot_truth))
	{
		success_count += 1;
		success("vec3_dot({3, -6, 4.5}, {-8.42362, 5, 2.3982835})\n");
	}
	else
	{
		failed("vec3_dot({3, -6, 4.5}, {-8.42362, 5, 2.3982835})\n");
		print_vec(vec);
		print_vec(truth);
	}

	dot = vec3_dot(vec3_new(0, 0, 0), vec3_new(0, 0, 0));
	dot_truth = 0.0;

	*number_of_tests += 1;
	if (fc(dot, dot_truth))
	{
		success_count += 1;
		success("vec3_dot({0, 0, 0}, {0, 0, 0})\n");
	}
	else
	{
		failed("vec3_dot({0, 0, 0}, {0, 0, 0})\n");
		print_vec(vec);
		print_vec(truth);
	}

	vec = vec3_cross(vec3_new(2, 2, 2), vec3_new(2, 2, 2));
	truth = (t_vec3){ 0, 0, 0 };

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec3_cross({2, 2, 2}, {2, 2, 2})\n");
	}
	else
	{
		failed("vec3_cross({2, 2, 2}, {2, 2, 2})\n");
		print_vec(vec);
		print_vec(truth);
	}

	vec = vec3_cross(vec3_new(4.237895235, -1, 3.5), vec3_new(0, -2.5325, -1.09275));
	truth = vec3_new(9.9565, 4.63096, -10.73247);

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec3_cross({4.237895235, -1, 3.5}, {0, -2.5325, -1.09275})\n");
	}
	else
	{
		failed("vec3_cross({4.237895235, -1, 3.5}, {0, -2.5325, -1.09275})\n");
		print_vec(vec);
		print_vec(truth);
	}

	vec = vec3_rot(vec3_new(1, 0, 0), vec3_new(0, 0, M_PI / 2));
	truth = vec3_new(0, 1, 0);

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec3_rot({1, 0, 0}, {0, 0, M_PI / 2})\n");
	}
	else
	{
		failed("vec3_rot({1, 0, 0}, {0, 0, M_PI / 2})\n");
		print_vec(vec);
		print_vec(truth);
	}

	vec = vec3_rot(vec3_new(1, 0, 0), vec3_new(0, 0, - M_PI / 2));
	truth = vec3_new(0, -1, 0);

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec3_rot({1, 0, 0}, {0, 0, - M_PI / 2})\n");
	}
	else
	{
		failed("vec3_rot({1, 0, 0}, {0, 0, - M_PI / 2})\n");
		print_vec(vec);
		print_vec(truth);
	}
	
	vec = vec3_rot(vec3_new(1, 0, 0), vec3_new(0, M_PI / 2, 0));
	truth = vec3_new(0, 0, -1);

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec3_rot({1, 0, 0}, {0, M_PI / 2, 0})\n");
	}
	else
	{
		failed("vec3_rot({1, 0, 0}, {0, M_PI / 2, 0})\n");
		print_vec(vec);
		print_vec(truth);
	}

	vec = vec3_rot(vec3_new(1, 0, 0), vec3_new(0, -M_PI / 2, 0));
	truth = vec3_new(0, 0, 1);

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec3_rot({1, 0, 0}, {0, -M_PI / 2, 0})\n");
	}
	else
	{
		failed("vec3_rot({1, 0, 0}, {0, -M_PI / 2, 0})\n");
		print_vec(vec);
		print_vec(truth);
	}
	
	vec = vec3_rot(vec3_new(0, 1, 1), vec3_new(M_PI / 2, 0, 0));
	truth = vec3_new(0, -1, 1);

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec3_rot({0, 1, 1}, {M_PI / 2, 0, 0})\n");
	}
	else
	{
		failed("vec3_rot({0, 1, 1}, {M_PI / 2, 0, 0})\n");
		print_vec(vec);
		print_vec(truth);
	}

	vec = vec3_rot(vec3_new(0, 1, 1), vec3_new(-M_PI / 2, 0, 0));
	truth = vec3_new(0, 1, -1);

	*number_of_tests += 1;
	if (fc(vec.x, truth.x) && fc(vec.y, truth.y) && fc(vec.z, truth.z))
	{
		success_count += 1;
		success("vec3_rot({0, 1, 1}, {-M_PI / 2, 0, 0})\n");
	}
	else
	{
		failed("vec3_rot({0, 1, 1}, {-M_PI / 2, 0, 0})\n");
		print_vec(vec);
		print_vec(truth);
	}

	return success_count;
}
