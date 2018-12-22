/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_vec_mult.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:58:11 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/21 18:03:49 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline t_fvec3			fvec3_mult(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3) {
		f_mul(a.x, b.x),
		f_mul(a.y, b.y),
		f_mul(a.z, b.z)
	});
}

inline t_fvec3			fvec3_scale(t_fvec3 a, t_fixed s)
{
	return ((t_fvec3) {
		f_mul(a.x, s),
		f_mul(a.y, s),
		f_mul(a.z, s)
	});
}

inline t_fvec2			fvec2_mult(t_fvec2 a, t_fvec2 b)
{
	return ((t_fvec2) {
		f_mul(a.u, b.u),
		f_mul(a.v, b.v)
	});
}

inline t_fvec2			fvec2_scale(t_fvec2 a, t_fixed s)
{
	return ((t_fvec2) {
		f_mul(a.u, s),
		f_mul(a.v, s)
	});
}
