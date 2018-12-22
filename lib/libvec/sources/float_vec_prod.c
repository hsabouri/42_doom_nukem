/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_prod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:37:37 by hugo              #+#    #+#             */
/*   Updated: 2018/12/22 13:35:09 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

static inline t_vec3	vec2_vec3(t_vec2 a)
{
	return ((t_vec3) {a.u, a.v, 0});
}

inline float			vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline float			vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.u * b.u + a.v * b.v);
}

inline t_vec3			vec3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3_new(
		a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x));
}

inline t_vec3			vec2_cross(t_vec2 a, t_vec2 b)
{
	const t_vec3	a3 = vec2_vec3(a);
	const t_vec3	b3 = vec2_vec3(b);

	return (vec3_new(
		a3.y * b3.z - a3.z * b3.y,
		a3.z * b3.x - a3.x * b3.z,
		a3.x * b3.y - a3.y * b3.x));
}
