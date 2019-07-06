/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 18:05:00 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/06 14:50:09 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "../color.h"

t_color			get_wall_pixel(t_proj proj, int y)
{
	t_fvec2	pix;
	t_color	res;

	pix.u = proj.x;
	pix.v = proj.y_iter * (y - proj.top) + proj.y_start;
	proj.tex_wall.p = W_PRECISION;
	res = get_mat_pixel(proj.tex_wall.mat, proj.tex_wall, pix, y);
	return (fog(res, f_mul(proj.dis, proj.dis)));
}

t_color			get_portal_pixel(t_proj proj, int y)
{
	t_fvec2	pix;
	t_color	res;

	pix.u = proj.x;
	pix.v = proj.y_iter * (y - proj.top) + proj.y_start;
	proj.tex_open.p = W_PRECISION;
	res = get_mat_pixel(proj.tex_open.mat, proj.tex_open, pix, y);
	return (fog(res, f_mul(proj.dis, proj.dis)));
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
	pix.u = proj.line.x.u + f_mul(t, proj.line.x.v) + proj.tex_pos.u;
	pix.v = proj.line.y.u + f_mul(t, proj.line.y.v) + proj.tex_pos.v;
	dis.x = pix.u + proj.center.u - proj.pos.u;
	dis.y = pix.v + proj.center.v - proj.pos.v;
	dis.z = f_mul(dis.x, dis.x) + f_mul(dis.y, dis.y);
	tex.p = 0;
	return (fog(get_mat_pixel(tex.mat, tex, pix, y), dis.z));
}

t_color			get_floor_pixel(t_pl_proj proj, t_tex_proj tex, int y)
{
	t_fvec2	pix;
	t_fixed	t;
	t_fvec3	dis;

	proj.line.z.v = proj.z_zero - proj.z_diff * y;
	t = (f_mul(proj.floor.x, proj.line.x.v) + f_mul(proj.floor.y,
		proj.line.y.v) - proj.line.z.v);
	if (t == 0)
		return (NO_COLOR);
	t = f_div((-proj.floor.z - f_mul(proj.floor.x, proj.line.x.u)
	- f_mul(proj.floor.y, proj.line.y.u) + proj.line.z.u),
	(f_mul(proj.floor.x, proj.line.x.v) + f_mul(proj.floor.y,
		proj.line.y.v) - proj.line.z.v));
	pix.u = proj.line.x.u + f_mul(t, proj.line.x.v) + proj.tex_pos.u;
	pix.v = proj.line.y.u + f_mul(t, proj.line.y.v) + proj.tex_pos.v;
	dis.x = pix.u + proj.center.u - proj.pos.u;
	dis.y = pix.v + proj.center.v - proj.pos.v;
	dis.z = f_mul(dis.x, dis.x) + f_mul(dis.y, dis.y);
	tex.p = 0;
	return (fog(get_mat_pixel(tex.mat, tex, pix, y), dis.z));
}

t_color			get_entity_pixel(t_e_proj proj, int y)
{
	t_fvec2	pix;
	t_color	res;

	pix.u = proj.x;
	pix.v = proj.y_iter * (y - proj.top);
	proj.tex.p = E_PRECISION;
	res = get_mat_pixel(proj.mat, proj.tex, pix, y);
	return (fog(res, f_mul(proj.dis, proj.dis)));
}
