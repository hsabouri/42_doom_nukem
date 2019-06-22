/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:05:08 by fmerding          #+#    #+#             */
/*   Updated: 2019/06/21 16:42:23 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <graphic.h>

t_proj	projection2(t_context context, t_proj res, t_fvec2 h)
{
	res.plane.wr.u = f_div(-h.v, f_mul((f_from_int(HEIGHT) / WIDTH),
		f_from_float(PWIDTH)));
	res.plane.wr.v = f_div(-h.u, f_mul((f_from_int(HEIGHT) / WIDTH),
		f_from_float(PWIDTH)));
	res.plane.look_v = f_to_int(context.physic.look_v * 100);
	res.tex_wall.ambient = context.sector.ambient;
	res.plane.tex_floor.ambient = context.sector.ambient;
	res.plane.tex_roof.ambient = context.sector.ambient;
	res.plane.floor.x = f_from_float(context.sector.floor.x);
	res.plane.floor.y = f_from_float(context.sector.floor.y);
	res.plane.floor.z = f_from_float(context.sector.floor.z);
	res.plane.ceiling.x = f_from_float(context.sector.ceiling.x);
	res.plane.ceiling.y = f_from_float(context.sector.ceiling.y);
	res.plane.ceiling.z = f_from_float(context.sector.ceiling.z);
	res.plane.center.u = f_from_float(context.sector.center.u);
	res.plane.center.v = f_from_float(context.sector.center.v);
	res.plane.height = context.height;
	res.plane.v_a = context.v_a;
	res.plane.v_b = context.v_b;
	res.plane.line.z.u = (res.plane.height);
	res.plane.tex_pos = context.sector.tex_pos;
	return (res);
}

t_fvec2	proj_h(t_fixed ratio, t_sector sector, t_cache_wall wall, t_ph physic)
{
	t_fixed	dis;
	t_fixed	dis2;
	t_fvec2 h;

	dis = find_z(sector, wall.left_z, 1) - find_z(sector, wall.right_z, 1);
	dis = f_mul(dis, ratio);
	dis2 = find_z(sector, wall.left_z, 0) - find_z(sector, wall.right_z, 0);
	dis2 = f_mul(dis2, ratio);
	h.u = f_from_float((physic.pos.z + physic.height))
	- find_z(sector, wall.left_z, 1) + dis;
	h.v = f_from_float((physic.pos.z + physic.height))
	- find_z(sector, wall.left_z, 0) + dis2;
	return (h);
}

t_fvec2	proj_hp(t_fixed ratio, t_sector sector, t_cache_wall wall, t_ph physic)
{
	t_fixed	dis;
	t_fixed	dis2;
	t_fvec2 h;

	dis = find_z(sector, wall.left_p, 1) - find_z(sector, wall.right_p, 1);
	dis = f_mul(dis, ratio);
	dis2 = find_z(sector, wall.left_p, 0) - find_z(sector, wall.right_p, 0);
	dis2 = f_mul(dis2, ratio);
	h.u = f_from_float((physic.pos.z + physic.height))
	- find_z(sector, wall.left_p, 1) + dis;
	h.v = f_from_float((physic.pos.z + physic.height))
	- find_z(sector, wall.left_p, 0) + dis2;
	return (h);
}
