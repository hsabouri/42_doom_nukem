/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:19:36 by hugo              #+#    #+#             */
/*   Updated: 2019/01/30 16:04:03 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float_math.h>

inline float	fast_inv_sqrt(float x)
{
	const float		xhalf = 0.5 * x;
	const int		magic = 0x5f3759df;
	t_inv_sqrt		u;

	u.x = x;
	u.i = magic - (u.i >> 1);
	u.x *= (1.5 - xhalf * u.x * u.x);
	u.x *= (1.5 - xhalf * u.x * u.x);
	return (u.x);
}

inline float	fast_sqrt(float x)
{
	const int	magic = -0x4c0000;
	t_sqrt		u;

	u.x = x;
	u.i = (1 << 29) + (u.i >> 1) - (1 << 22) + magic;
	u.x = 0.5 * (u.x + x / u.x);
	u.x = 0.5 * (u.x + x / u.x);
	u.x = 0.5 * (u.x + x / u.x);
	return (u.x);
}

inline float	clamp(float x, float min, float max)
{
	if (x > max)
		return (max);
	else if (x < min)
		return (min);
	else
		return (x);
}
