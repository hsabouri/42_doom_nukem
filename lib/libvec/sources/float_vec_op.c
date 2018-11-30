/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:34:29 by hugo              #+#    #+#             */
/*   Updated: 2018/11/29 15:53:01 by hugo             ###   ########.fr       */
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

inline t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_new(
		a.x * a.s + b.x * b.s,
		a.y * a.s + b.y * b.s,
		a.z * a.s + b.z * b.s
	));
}

inline t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return (vec2_new(
		a.u * a.s + b.u * b.s,
		a.v * a.s + b.v * b.s
	));
}