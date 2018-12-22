/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_vec_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:54:19 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/21 18:06:13 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline t_fvec3		fvec3_add(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3) {
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	});
}

inline t_fvec3		fvec3_sub(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3) {
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	});
}

inline t_fvec2		fvec2_add(t_fvec2 a, t_fvec2 b)
{
	return ((t_fvec2) {
		a.u + b.u,
		a.v + b.v,
	});
}

inline t_fvec2		fvec2_sub(t_fvec2 a, t_fvec2 b)
{
	return ((t_fvec2) {
		a.u - b.u,
		a.v - b.v,
	});
}
