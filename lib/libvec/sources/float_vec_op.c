/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:34:29 by hugo              #+#    #+#             */
/*   Updated: 2019/05/31 14:36:18 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x - b.x, a.y - b.y, a.z - b.z));
}

inline t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	return (vec2_new(a.u - b.u, a.v - b.v));
}

inline t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x + b.x, a.y + b.y, a.z + b.z));
}

inline t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return (vec2_new(a.u + b.u, a.v + b.v));
}

inline float	vec2_sq_size(t_vec2 a)
{
	return (a.u * a.u + a.v * a.v);
}
