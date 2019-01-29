/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:31:19 by hugo              #+#    #+#             */
/*   Updated: 2018/12/22 13:32:22 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline float	vec3_inv_size(t_vec3 a)
{
	return (fast_inv_sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

inline float	vec2_inv_size(t_vec2 a)
{
	return (fast_inv_sqrt(a.u * a.u + a.v * a.v));
}

inline t_vec2	vec2_normalize(t_vec2 a)
{
	const float i_size = vec2_inv_size(a);

	return (vec2_scale(a, i_size));
}

inline t_vec3	vec3_new(float x, float y, float z)
{
	return ((t_vec3) {x, y, z});
}

inline t_vec2	vec2_new(float u, float v)
{
	return ((t_vec2) {u, v});
}