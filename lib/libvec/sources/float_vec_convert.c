/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 12:22:53 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/24 14:42:07 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline t_vec2	vec3_to_vec2(t_vec3 vec)
{
	return ((t_vec2)
	{
		vec.x, vec.y
	});
}

inline t_vec3	vec2_to_vec3(t_vec2 vec)
{
	return ((t_vec3)
	{
		vec.u, vec.v, 0
	});
}

inline t_vec3	fvec3_to_vec3(t_fvec3 fvec)
{
	return ((t_vec3)
	{
		f_to_float(fvec.x),
		f_to_float(fvec.y),
		f_to_float(fvec.z)
	});
}

inline t_vec2	fvec2_to_vec2(t_fvec2 fvec)
{
	return ((t_vec2)
	{
		f_to_float(fvec.u),
		f_to_float(fvec.v)
	});
}
