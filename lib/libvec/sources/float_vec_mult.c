/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_mult.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:09:00 by hugo              #+#    #+#             */
/*   Updated: 2019/05/31 14:36:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline t_vec3	vec3_scale(t_vec3 vec, float s)
{
	return ((t_vec3)
	{
		vec.x * s,
		vec.y * s,
		vec.z * s
	});
}

inline t_vec2	vec2_scale(t_vec2 vec, float s)
{
	return ((t_vec2)
	{
		vec.u * s,
		vec.v * s
	});
}

inline t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x * b.x, a.y * b.y, a.z * b.z));
}

inline t_vec2	vec2_mult(t_vec2 a, t_vec2 b)
{
	return (vec2_new(a.u * b.u, a.v * b.v));
}

inline float	vec3_sq_size(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}
