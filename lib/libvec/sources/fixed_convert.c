/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:08:10 by hugo              #+#    #+#             */
/*   Updated: 2018/11/28 11:10:48 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fixed_math.h>

inline int32_t		f_to_int(t_fixed num)
{
	return (num >> SUB_BITS);
}

inline t_fixed		f_from_int(int32_t num)
{
	return (num << SUB_BITS);
}

static float   power_of(float to_convert, const int power, int neg)
{
	int i;

	i = 0;
    while (i < power)
	{
		if (neg)
			to_convert /= 2;
		else
			to_convert *= 2;
		i++;
    }
    return to_convert;
}

/*
* only use it to test
*/

inline float		f_to_float(t_fixed num)
{
	const int32_t	int_part = f_to_int(num);
	const int32_t	mantis = num << (sizeof(t_fixed) * 8 - SUB_BITS)\
								>> (sizeof(t_fixed) * 8 - SUB_BITS);
	const float		decimal = power_of((float)mantis, SUB_BITS, 1);

	return ((float)int_part + decimal);
}

t_fixed				f_from_float(float val)
{
	const int64_t	contains = (int64_t)power_of(val, 14, 0);
	const t_fixed	res = (int32_t)contains;

	return (res);
}
