/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_mult.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:09:00 by hugo              #+#    #+#             */
/*   Updated: 2018/12/20 13:45:13 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline t_vec3	vec3_scale(t_vec3 vec, float s)
{
	return ((t_vec3) {
		vec.x, vec.y,
		vec.s * s,
		vec.z
	});
}

inline t_vec2	vec2_scale(t_vec2 vec, float s)
{
	return ((t_vec2) {
		vec.u,
		vec.v,
		vec.s * s
	});
}

inline t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	const float	ab = a.s * b.s;
	
	return (vec3_new(
		a.x * b.x * ab,\
		a.y * b.y * ab,\
		a.z * b.z * ab
	));
}

inline t_vec2	vec2_mult(t_vec2 a, t_vec2 b)
{
	const float	ab = a.s * b.s;
	
	return (vec2_new(
		a.u * b.u * ab,\
		a.v * b.v * ab
	));
}