/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:19:15 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/10 15:27:52 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./color.h"

t_color			get_mat_pixel(t_mat mat, t_tex_proj tex, t_fvec2 pix,
	char p, int y_s)
{
	int		x;
	int		y;
	t_img	img;
	t_color	res;

	if (!mat.texture)
		res = mat.color;
	else
	{
		img = *mat.texture;
		if (mat.mode == SKYBOX)
		{
			x = f_to_int((tex.x * mat.sca.u - mat.pos.u)) % img.width;
			y = f_to_int((y_s - tex.angle) * mat.sca.v - mat.pos.v)
			% img.height;
		}
		else
		{
			x = f_to_int((f_mul(pix.u, mat.sca.u) - mat.pos.u) * img.width);
			y = f_to_int((f_mul(pix.v, mat.sca.v) - mat.pos.v) * img.height)
			>> p;
		}
		if (mat.mode == TILING)
		{
			y = y % img.height;
			x = x % img.width;
		}
		if ((uint)x >= img.width || x < 0 || (uint)y >= img.height || y < 0)
			res = mat.color;
		else
			res = color_filter(img.content[x + y * img.width], mat.filter);
	}
	if (mat.overlay)
		res = color_superpose(res, get_mat_pixel(*mat.overlay, tex, pix, p,
			y_s));
	if (mat.mode != SKYBOX)
		return (color_filter(res, tex.ambient));
	else
		return (res);
}

static t_color	fog(t_color color, t_fixed u)
{
	const int	min = 20;

	if (u <= f_from_int(min))
		return (color);
	color.r = f_to_int(f_div(f_from_int(color.r * min), u));
	color.g = f_to_int(f_div(f_from_int(color.g * min), u));
	color.b = f_to_int(f_div(f_from_int(color.b * min), u));
	return (color);
}

t_color			get_wall_pixel(t_proj proj, int y)
{
	t_fvec2	pix;
	t_color	res;

	pix.u = proj.x;
	pix.v = proj.y_iter * (y - proj.top) + proj.y_start;
	res = get_mat_pixel(proj.tex_wall.mat, proj.tex_wall, pix, 9, y);
	return (fog(res, proj.dis));
}

t_color			get_portal_pixel(t_proj proj, int y)
{
	t_fvec2	pix;
	t_color	res;

	pix.u = proj.x;
	pix.v = proj.y_iter * (y - proj.top) + proj.y_start;
	res = get_mat_pixel(proj.tex_open.mat, proj.tex_open, pix, 9, y);
	return (fog(res, proj.dis));
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

t_color			get_roof_pixel(t_pl_proj proj, t_tex_proj tex, int y)
{
	t_fvec2	pix;
	t_fixed	t;
	t_fvec3	dis;

	proj.line.z.v = proj.z_zero - proj.z_diff * y;
	t = (f_mul(proj.ceiling.x, proj.line.x.v) + f_mul(proj.ceiling.y,
		proj.line.y.v) - proj.line.z.v);
	if (t == 0)
		return (NO_COLOR);
	t = f_div((-proj.ceiling.z - f_mul(proj.ceiling.x, proj.line.x.u)
	- f_mul(proj.ceiling.y, proj.line.y.u) + proj.line.z.u),
	(f_mul(proj.ceiling.x, proj.line.x.v) + f_mul(proj.ceiling.y,
		proj.line.y.v) - proj.line.z.v));
	pix.u = proj.line.x.u + f_mul(t, proj.line.x.v);
	pix.v = proj.line.y.u + f_mul(t, proj.line.y.v);
	dis.x = f_to_float(pix.u + proj.center.u - proj.pos.u);
	dis.y = f_to_float(pix.v + proj.center.v - proj.pos.v);
	dis.z = fast_sqrt(dis.x * dis.x + dis.y * dis.y);
	return (fog(get_mat_pixel(tex.mat, tex, pix, 0, y), f_from_float(dis.z)));
}

t_color			get_floor_pixel(t_pl_proj proj, t_tex_proj tex, int y)
{
	t_fvec2	pix;
	t_fixed	t;
	t_vec3	dis;

	proj.line.z.v = proj.z_zero - proj.z_diff * y;
	t = (f_mul(proj.floor.x, proj.line.x.v) + f_mul(proj.floor.y,
		proj.line.y.v) - proj.line.z.v);
	if (t == 0)
		return (NO_COLOR);
	t = f_div((-proj.floor.z - f_mul(proj.floor.x, proj.line.x.u)
	- f_mul(proj.floor.y, proj.line.y.u) + proj.line.z.u),
	(f_mul(proj.floor.x, proj.line.x.v) + f_mul(proj.floor.y,
		proj.line.y.v) - proj.line.z.v));
	pix.u = proj.line.x.u + f_mul(t, proj.line.x.v);
	pix.v = proj.line.y.u + f_mul(t, proj.line.y.v);
	dis.x = f_to_float(pix.u + proj.center.u - proj.pos.u);
	dis.y = f_to_float(pix.v + proj.center.v - proj.pos.v);
	dis.z = fast_sqrt(dis.x * dis.x + dis.y * dis.y);
	return (fog(get_mat_pixel(tex.mat, tex, pix, 0, y), f_from_float(dis.z)));
}

t_color			get_entity_pixel(t_e_proj proj, int y)
{
	t_fvec2	pix;
	t_color	res;

	pix.u = proj.x;
	pix.v = proj.y_iter * (y - proj.top);
	res = get_mat_pixel(proj.mat, proj.tex, pix, 8, y);
	return (fog(res, proj.dis));
}
