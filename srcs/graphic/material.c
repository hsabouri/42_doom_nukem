/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:19:15 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/06 13:40:09 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

static t_color	color_filter(t_color a, t_color filter)
{
	return ((t_color) {
		.a = (a.a * filter.a) >> 8,
		.b = (a.b * filter.b) >> 8,
		.g = (a.g * filter.g) >> 8,
		.r = (a.r * filter.r) >> 8,
	});
}

static t_color	color_superpose(t_color a, t_color b)
{
	if (b.a)
		return (b);
	else
		return (a);
}

static t_color	get_mat_pixel(t_mat mat, t_tex_proj tex, t_fvec2 pix, char p, int y_s)
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
			y = f_to_int((y_s - tex.angle) * mat.sca.v - mat.pos.v) % img.height;
		}
		else
		{
			x = f_to_int((f_mul(pix.u, mat.sca.u) - mat.pos.u) * img.width);
			y = f_to_int((f_mul(pix.v, mat.sca.v) - mat.pos.v) * img.height) >> p;
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
		res = color_superpose(res, get_mat_pixel(*mat.overlay, tex, pix, p, y_s));
	if (mat.mode != SKYBOX)
		return (color_filter(res, tex.ambient));
	else
		return (res);
}

t_color			get_wall_pixel(t_proj proj, int y)
{
	t_fvec2 pix;

	pix.u = proj.x;
	pix.v = proj.y_iter * (y - proj.top);
	return (get_mat_pixel(proj.tex_wall.mat, proj.tex_wall, pix, 8, y));
}

t_color			get_roof_pixel(t_pl_proj proj, t_tex_proj tex, int y)
{
	t_fixed	z;
	t_fvec2	pix;

	z = f_from_int(HEIGHT / 2 - y + proj.look_v) / HEIGHT;
	if (z == 0)
		return (NO_COLOR);
	pix = fvec2_scale(proj.ray, f_div(proj.wr.u, z));
	pix = fvec2_add(pix, proj.pos);
	return (get_mat_pixel(tex.mat, tex, pix, 0, y));
}

t_color			get_floor_pixel(t_pl_proj proj, t_tex_proj tex, int y)
{
	t_fixed	z;
	t_fvec2	pix;

	z = f_from_int(HEIGHT / 2 - y + proj.look_v) / HEIGHT;
	if (z == 0)
		return (NO_COLOR);
	pix = fvec2_scale(proj.ray, f_div(proj.wr.v, z));
	pix = fvec2_add(pix, proj.pos);
	return (get_mat_pixel(tex.mat, tex, pix, 0, y));
}

t_color			get_entity_pixel(t_e_proj proj, int y)
{
	t_fvec2	pix;
	t_color	res;

	pix.u = proj.x;
	pix.v = proj.y_iter * (y - proj.top); // here
	res = get_mat_pixel(proj.mat, proj.tex, pix, 8, y);
	return (res);
}