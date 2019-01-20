/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 13:10:36 by hugo              #+#    #+#             */
/*   Updated: 2019/01/20 17:57:00 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fixed_math.h>

inline t_fixed		f_mul(t_fixed a, t_fixed b)
{
	const int64_t res = (int64_t)a * (int64_t)b;

	return ((t_fixed)(res >> SUB_BITS));
}

inline t_fixed		f_div(t_fixed a, t_fixed b)
{
	const int64_t	d_a = ((int64_t)a) << SUB_BITS;
	const int64_t	d_b = (int64_t)b;

	return ((t_fixed)(d_a / d_b));
}

inline t_fixed		f_add_int(t_fixed a, int32_t b)
{
	return (a + f_from_int(b));
}

inline t_fixed		f_sub_int(t_fixed a, int32_t b)
{
	return (a - f_from_int(b));
}
