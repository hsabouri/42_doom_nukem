/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_prod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:37:37 by hugo              #+#    #+#             */
/*   Updated: 2018/11/29 19:05:53 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

static inline t_vec3	vec2_vec3(t_vec2 a)
{
	return ((t_vec3) {a.u, a.v, a.s, 0});
}

inline float			vec3_dot(t_vec3 a, t_vec3 b)
{
	return (
		a.x * a.s * b.x * b.s +\
		a.y * a.s * b.y * b.s +\
		a.z * a.s * b.z * b.s
	);
}

inline float			vec2_dot(t_vec2 a, t_vec2 b)
{
	return (
		a.u * a.s * b.u * b.s +\
		a.v * a.s * b.v * b.s
	);
}

inline t_vec3			vec3_cross(t_vec3 a, t_vec3 b)
{
	const float	ab = a.s * b.s;

	return (vec3_new(
		(a.y * b.z - a.z * b.y) * ab,
		(a.z * b.x - a.x * b.z) * ab,
		(a.x * b.y - a.y * b.x) * ab
	));
}

inline t_vec3			vec2_cross(t_vec2 a, t_vec2 b)
{
	const t_vec3	a3 = vec2_vec3(a);
	const t_vec3	b3 = vec2_vec3(b);
	const float 	ab = a.s * b.s;

	return (vec3_new(
		(a3.y * b3.z - a3.z * b3.y) * ab,
		(a3.z * b3.x - a3.x * b3.z) * ab,
		(a3.x * b3.y - a3.y * b3.x) * ab
	));
}