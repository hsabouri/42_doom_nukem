/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_sqrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:27:47 by hugo              #+#    #+#             */
/*   Updated: 2018/11/28 18:54:18 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fixed_math.h>

inline t_fixed		f_inv_sqrt(t_fixed n)
{
	const float		f_n = f_to_float(n);
	int64_t			i;
	t_fixed			x2;
	t_fixed			res;


	x2 = n >> 1;
	i = *(int64_t *)&f_n;
	i = 0x5f3759df - (i >> 1);
	res = f_from_float(*(float *)&i);
	res = res * (0x6000 - (x2 * res * res));
	res = res * (0x6000 - (x2 * res * res));
	return (res);
}

inline t_fixed		f_sqrt(t_fixed n)
{
	const float	f_n = f_to_float(n);
	
	return (f_from_float(sqrt(f_n)));
}