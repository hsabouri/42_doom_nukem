/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_mult.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:09:00 by hugo              #+#    #+#             */
/*   Updated: 2018/11/29 19:40:11 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

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