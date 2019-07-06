/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:19:15 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/06 14:12:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "../color.h"

static t_color	texture_mode(t_mat mat, t_tex_proj tex, t_fvec2 pix, int y_s)
{
	t_img	img;
	t_pix	coords;

	img = *mat.texture;
	if (mat.mode == SKYBOX)
		coords = (t_pix) {f_to_int((tex.x * mat.sca.u - mat.pos.u))
			% img.width, f_to_int((y_s - tex.angle) * mat.sca.v - mat.pos.v)
			% img.height};
	else
		coords = (t_pix) {f_to_int((f_mul(pix.u, mat.sca.u) - mat.pos.u)
			* img.width), f_to_int((f_mul(pix.v, mat.sca.v) - mat.pos.v)
			* img.height) >> tex.p};
	if (mat.mode == TILING)
		coords = (t_pix) {coords.x % img.width, coords.y % img.height};
	if ((uint)coords.x >= img.width || coords.x < 0
		|| (uint)coords.y >= img.height || coords.y < 0)
		return (mat.color);
	else
		return (color_filter(img.content[coords.x + coords.y * img.width],
			mat.filter));
}

t_color			get_mat_pixel(t_mat mat, t_tex_proj tex, t_fvec2 pix, int y_s)
{
	t_color	res;

	if (!mat.texture)
		res = mat.color;
	else
		res = texture_mode(mat, tex, pix, y_s);
	if (mat.overlay)
		res = color_superpose(res, get_mat_pixel(*mat.overlay, tex, pix,
			y_s));
	if (mat.mode != SKYBOX)
		return (color_filter(res, tex.ambient));
	else
		return (res);
}

t_color			fog(t_color color, t_fixed u)
{
	const int	min = 300;

	if (u <= f_from_int(min))
		return (color);
	color.r = f_to_int(f_div(f_from_int(color.r * min), u));
	color.g = f_to_int(f_div(f_from_int(color.g * min), u));
	color.b = f_to_int(f_div(f_from_int(color.b * min), u));
	return (color);
}

t_pl_proj		find_line(t_fvec2 center, t_pl_proj plane, t_fixed ratio)
{
	t_fvec2 vec;
	t_fixed diffx;
	t_fixed diffy;
	t_fixed res;

	diffx = plane.v_b.u - plane.v_a.u;
	diffy = plane.v_b.v - plane.v_a.v;
	vec.u = plane.v_a.u + f_mul(ratio, diffx);
	vec.v = plane.v_a.v + f_mul(ratio, diffy);
	plane.line.x.v = vec.u;
	plane.line.y.v = vec.v;
	plane.line.x.u = plane.pos.u - center.u;
	plane.line.y.u = plane.pos.v - center.v;
	res = f_from_float((HEIGHT / 2.0) * (PWIDTH / WIDTH));
	plane.z_zero = res + f_from_int(plane.look_v) * (PWIDTH / WIDTH);
	plane.z_diff = f_div(res, f_from_float(360.0));
	return (plane);
}
