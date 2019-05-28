/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:19:15 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/28 14:28:21 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./color.h"


t_color			get_mat_pixel(t_mat mat, t_tex_proj tex, t_fvec2 pix, char p, int y_s)
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
	pix.v = proj.y_iter * (y - proj.top) + proj.y_start;
	return (get_mat_pixel(proj.tex_wall.mat, proj.tex_wall, pix, 9, y));
}

t_color			get_portal_pixel(t_proj proj, int y)
{
	t_fvec2 pix;

	pix.u = proj.x;
	pix.v = proj.y_iter * (y - proj.top) + proj.y_start;
	return (get_mat_pixel(proj.tex_open.mat, proj.tex_open, pix, 9, y));
}

t_pl_proj	find_line(t_fvec2 center, t_pl_proj plane, t_fixed ratio, t_sector sector)
{
	t_fvec2 vec;
	t_fixed diffx;
	t_fixed diffy;
	// t_fixed	dis;
	t_fixed res;
	diffx = plane.v_b.u - plane.v_a.u;
	diffy = plane.v_b.v - plane.v_a.v;
	//(need coordonnee collision mur / rayon)
	// printf("leftu = %f  = %f\n",f_to_float(plane.v_a.u) ,f_to_float(plane.v_a.v) );
	// printf("right  = %f = %f\n",f_to_float(plane.v_b.u) ,f_to_float(plane.v_b.v) );
	vec.u = plane.v_a.u + f_mul(ratio, diffx); // vecteur x;
	vec.v = plane.v_a.v + f_mul(ratio, diffy); // vecteur y;
	plane.line.x.v = vec.u;
	plane.line.y.v = vec.v;
	plane.line.x.u = plane.pos.u - center.u;
	plane.line.y.u = plane.pos.v - center.v;
	res = f_from_float(0.703125);
	// dis = 0.703125;

	plane.z_zero = res + plane.line.z.u;
	// dis = sqrtf(f_to_float(f_mul(diffx,diffx) + f_mul(diffy,diffy)));
	// printf("dis = %f",dis);
	// point.u = f_to_float(plane.pos.u + vec.u);
	// point.v = f_to_float(plane.pos.v + vec.v);
	// plane.z_zero = find_z(sector,point,0) - plane.line.z.u;
	// max = find_z(sector,point,1) - plane.line.z.u;
	// plane.z_diff = f_div((max - plane.z_zero),f_from_float(720.0));
	plane.z_diff = f_div(res,f_from_float(360.0));
	// printf("zero = %f diff = %f \n",f_to_float(plane.z_zero),f_to_float(plane.z_diff));
	// plane.ppd
	// plane.line.x.v = point.u - plane.pos.u;
	// plane.line.y.v = point.v - plane.pos.v;
	// if (f_to_float(ratio) < 0.02)
	// printf("gauche p.u =%f, p.v = %f\n",f_to_float(plane.line.x.u), f_to_float(plane.line.y.u));
	// if (f_to_float(ratio) > 0.49 && f_to_float(ratio) < 0.51)
	// printf("droite p.u =%f, p.v = %f\n",f_to_float(plane.line.x.u), f_to_float(plane.line.y.u));
// printf("ratio = %f\n",f_to_float(ratio));
// if (f_to_float(ratio) > 0.49 && f_to_float(ratio) < 0.51)
// {
// printf("ratio = %f x =  %f + %f * t  y =  %f + %f t \n",f_to_float(ratio),f_to_float(plane.line.x.u),f_to_float(plane.line.x.v),f_to_float(plane.line.y.u), f_to_float(plane.line.y.v));
// }
	// dif = f_div(plane.line.x, plane.line.y);

	// plane.line.y = f_div(plane.line.x, dif);
	// plane.line.x = 1;
	// if (plane.line.x < 0)
	// plane.line.x = -1;
	return (plane);
}

t_color			get_roof_pixel(t_pl_proj proj, t_tex_proj tex, int y)
{
	t_fixed	z;
	t_fvec2	pix;
	t_fixed t;
	// proj.line.z.u = proj.height + find_z(); // FIND Z
	proj.line.z.v = f_from_float(0.703125) - proj.z_diff * y;
	// proj.line.z.v = f_from_float(0.5);

	t = (f_mul(proj.ceiling.x, proj.line.x.v) + f_mul(proj.ceiling.y, proj.line.y.v) - proj.line.z.v);
	// printf("t =%d",t);
	// if (y == 0)
	// 	printf(" x =  %f + %f * t  y =  %f + %f t z = %f + %f t  \n",f_to_float(proj.line.x.u),f_to_float(proj.line.x.v),f_to_float(proj.line.y.u), f_to_float(proj.line.y.v),f_to_float(proj.line.z.u),f_to_float(proj.line.z.v));
	if (t == 0)
			return (NO_COLOR);
	if (proj.ceiling.x == 0 && proj.ceiling.y == 0)
	{
		z = f_from_int(HEIGHT / 2 - y + proj.look_v) / HEIGHT;
		// printf("proj.look_v = %d y = %d z = %f\n",proj.look_v,y,f_to_float(z));
		if (z == 0)
				return (NO_COLOR);
		pix = fvec2_scale(proj.ray, f_div(proj.wr.u, z));
		pix = fvec2_add(pix, proj.pos);
		return (get_mat_pixel(tex.mat, tex, pix, 0, y));
	}
	if (t == 0)
		return(NO_COLOR);
		// t = f_from_float(0.001);
	t = f_div((- proj.ceiling.z - f_mul(proj.ceiling.x, proj.line.x.u) -f_mul(proj.ceiling.y,proj.line.y.u) + proj.line.z.u), (f_mul(proj.ceiling.x, proj.line.x.v) + f_mul(proj.ceiling.y, proj.line.y.v) - proj.line.z.v));
	pix.u = proj.line.x.u + f_mul(t, proj.line.x.v);
	pix.v = proj.line.y.u + f_mul(t, proj.line.y.v);
// if (y == 0)
// 	printf("t = %f pix.x = %f pix.y = %f\n",f_to_float(t), f_to_float(pix.u),f_to_float(pix.v));

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
	pix.v = proj.y_iter * (y - proj.top);
	res = get_mat_pixel(proj.mat, proj.tex, pix, 8, y);
	return (res);
}
