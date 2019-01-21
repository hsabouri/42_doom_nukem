/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 13:58:11 by hugo              #+#    #+#             */
/*   Updated: 2019/01/21 17:58:24 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

static t_color		color_filter(t_color a, t_color filter)
{
	return ((t_color) {
		.a = (a.a * filter.a) >> 8,
		.b = (a.b * filter.b) >> 8,
		.g = (a.g * filter.g) >> 8,
		.r = (a.r * filter.r) >> 8,
	});
}

static t_color		color_superpose(t_color a, t_color b)
{
	if (b.a)
		return (b);
	else
		return (a);
}

static t_color		get_mat_pixel(t_mat mat, t_color ambient, t_fvec2 pix, u_int8_t precision)
{
	int		x;
	int		y;
	t_img	tex;
	t_color	res;

	if (!mat.texture)
		res = mat.color;
	else
	{
		tex = *mat.texture;
		x = f_to_int((f_mul(pix.u, mat.sca.u) - mat.pos.u) * tex.width);
		y = (f_to_int((f_mul(pix.v, mat.sca.v) - (mat.pos.v << precision)) *\
			tex.height) >> precision);
		if (mat.mode == TILING)
		{
			y = y % tex.height;
			x = x % tex.width;
		}
		if ((uint)x >= tex.width || x < 0 || (uint)y >= tex.height || y < 0)
			res = mat.color;
		else
			res = color_filter(tex.content[x + y * tex.width], mat.filter);
	}
	if (mat.overlay)
		res = color_superpose(res,\
		get_mat_pixel(*mat.overlay, ambient, pix, precision));
	return (color_filter(res, ambient));
}

t_color				get_wall_pixel(t_mat mat, t_proj proj, int y)
{
	t_fvec2 pix;

	pix.u = proj.x_col;
	pix.v = (proj.y_iter * (proj.bot - y));
	return (get_mat_pixel(mat, proj.sector.ambient, pix, Y_PRECISION));
}

t_color				get_roof_pixel(t_mat mat, t_proj proj, int y)
{
	const t_fixed	wratio = f_mul((f_from_int(HEIGHT) / WIDTH), f_from_float(PWIDTH));
	t_fixed			z;
	t_fvec2			pix;

	z = f_from_int(HEIGHT / 2 - y) / HEIGHT;
	if (z == 0)
		return (NO_COLOR);
	pix = fvec2_scale(proj.ray,\
		f_div(f_div(-proj.h.v, wratio), z));
	pix.u += proj.pos.x;
	pix.v += proj.pos.y;
	return (get_mat_pixel(mat, proj.sector.ambient, pix, 0));
}

t_color				get_floor_pixel(t_mat mat, t_proj proj, int y)
{
	const t_fixed	wratio = f_mul((f_from_int(HEIGHT) / WIDTH), f_from_float(PWIDTH));
	t_fixed			z;
	t_fvec2			pix;

	z = f_from_int(HEIGHT / 2 - y) / HEIGHT;
	if (z == 0)
		return (NO_COLOR);
	pix = fvec2_scale(proj.ray,\
		f_div(f_div(-proj.h.u, wratio), z));
	pix.u += proj.pos.x;
	pix.v += proj.pos.y;
	return (get_mat_pixel(mat, proj.sector.ambient, pix, 0));
}

