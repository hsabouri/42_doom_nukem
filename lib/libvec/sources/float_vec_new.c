/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:31:19 by hugo              #+#    #+#             */
/*   Updated: 2018/11/29 19:12:39 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline float	vec3_size(t_vec3 a)
{
	return (fast_sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

inline float	vec2_size(t_vec2 a)
{
	return (fast_sqrt(a.u * a.u + a.v * a.v));
}

inline t_vec3	vec3_new(float x, float y, float z)
{
	const float	inv_sqrt = fast_inv_sqrt(x * x + y * y + z * z);

	return ((t_vec3) {\
		x * inv_sqrt,\
		y * inv_sqrt,\
		1 / inv_sqrt,\
		z * inv_sqrt\
	});
}

inline t_vec2	vec2_new(float u, float v)
{
	const float	inv_sqrt = fast_inv_sqrt(u * u + v * v);

	return ((t_vec2) {\
		u * inv_sqrt,\
		v * inv_sqrt,\
		1 / inv_sqrt\
	});
}