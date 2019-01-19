/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:08:10 by hugo              #+#    #+#             */
/*   Updated: 2019/01/19 17:07:02 by hsabouri         ###   ########.fr       */
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

inline float		f_to_float(t_fixed num)
{
	return (ldexpf((float)num, -SUB_BITS));
}

t_fixed				f_from_float(float val)
{
	return ((t_fixed)ldexpf(val, SUB_BITS));
}
