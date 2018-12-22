/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_vec_prod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 18:06:36 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/21 18:15:40 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

static inline t_fvec3	vec2_vec3(t_fvec2 a)
{
	return ((t_fvec3) {a.u, a.v, 0});
}

inline t_fixed			fvec3_dot(t_fvec3 a, t_fvec3 b)
{
	return (f_mul(a.x, b.x) + f_mul(a.y, b.y) + f_mul(a.z, b.z));
}

inline t_fvec3			fvec3_cross(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3) {
		f_mul(a.y, b.z) - f_mul(a.z, b.y),
		f_mul(a.z, b.x) - f_mul(a.x, b.z),
		f_mul(a.x, b.y) - f_mul(a.y, b.x)
	});
}

inline t_fixed			fvec2_dot(t_fvec2 a, t_fvec2 b)
{
	return (f_mul(a.u, b.u) + f_mul(a.v, b.v));
}

inline t_fvec3			fvec2_cross(t_fvec2 a, t_fvec2 b)
{
	const t_fvec3 a3 = vec2_vec3(a);
	const t_fvec3 b3 = vec2_vec3(b);

	return ((t_fvec3) {
		f_mul(a3.y, b3.z) - f_mul(a3.z, b3.y),
		f_mul(a3.z, b3.x) - f_mul(a3.x, b3.z),
		f_mul(a3.x, b3.y) - f_mul(a3.y, b3.x)
	});
}
