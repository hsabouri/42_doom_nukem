/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_vec_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:40:20 by hugo              #+#    #+#             */
/*   Updated: 2018/12/22 13:36:19 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec.h>

inline t_vec2	vec2_rot(t_vec2 a, float t)
{
	const float	tcos = cosf(t);
	const float	tsin = sinf(t);

	return ((t_vec2) {a.u * tcos - a.v * tsin, a.u * tsin + a.v * tcos});
}

inline t_vec3	vec3_rot_z(t_vec3 a, float t)
{
	const float	tcos = cosf(t);
	const float	tsin = sinf(t);

	return ((t_vec3) {a.x * tcos - a.y * tsin, a.x * tsin + a.y * tcos, a.z});
}

inline t_vec3	vec3_rot_x(t_vec3 a, float t)
{
	const float	tcos = cosf(t);
	const float	tsin = sinf(t);

	return ((t_vec3) {a.x, a.y * tcos - a.z * tsin, a.y * tsin + a.z * tcos});
}

inline t_vec3	vec3_rot_y(t_vec3 a, float t)
{
	const float	tcos = cosf(t);
	const float	tsin = sinf(t);

	return ((t_vec3) {a.z * tsin + a.x * tcos, a.y, a.z * tcos - a.x * tsin});
}

t_vec3			vec3_rot(t_vec3 a, t_vec3 r)
{
	t_vec3	res;

	res = vec3_rot_x(a, r.x);
	res = vec3_rot_y(res, r.y);
	res = vec3_rot_z(res, r.z);
	return (res);
}
