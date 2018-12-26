/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_vec_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 11:47:13 by hugo              #+#    #+#             */
/*   Updated: 2018/12/26 11:50:59 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

t_fvec3			vec3_to_fvec3(t_vec3 vec)
{
	return ((t_fvec3) {
		f_from_float(vec.x),
		f_from_float(vec.y),
		f_from_float(vec.z)
	});
}

t_fvec2			vec2_to_fvec2(t_vec2 vec)
{
	return ((t_fvec2) {
		f_from_float(vec.u),
		f_from_float(vec.v)
	});
}