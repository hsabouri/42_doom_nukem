/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:31:19 by hugo              #+#    #+#             */
/*   Updated: 2018/12/20 13:46:57 by hsabouri         ###   ########.fr       */
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
	return ((t_vec3) {\
		x,\
		y,\
		1,\
		z\
	});
}

inline t_vec2	vec2_new(float u, float v)
{
	return ((t_vec2) {\
		u,\
		v,\
		1\
	});
}