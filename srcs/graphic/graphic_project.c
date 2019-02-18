/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:15:51 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/18 15:57:21 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./graphic_project.h"
#include "../common/translate_id.h"
#include <signal.h>

static t_proj	project_portal(t_proj res, t_fvec2 top_bot, t_fvec2 h[2],
t_hit hit)
{
	if (res.tex_proj.wall.portal >= 0)
	{
		res.is_ceil = (h[1].v - h[0].v > 0) ? 1 : 0;
		res.is_step = (h[1].u - h[0].u < 0) ? 1 : 0;
		res.ceil = top_bot.u + f_div(RATIO * (h[1].v - h[0].v), hit.u);
		res.step = top_bot.v + f_div(RATIO * (h[1].u - h[0].u), hit.u);
		res.ceil = f_to_int((f_from_int(HEIGHT) >> 1) + res.ceil);
		res.step = f_to_int((f_from_int(HEIGHT) >> 1) + res.step);
		res.st_id = translate_in(PART_PORTAL, MOD_STEP, hit.wall, 0);
		res.tp_id = translate_in(PART_PORTAL, MOD_CEIL, hit.wall, 0);
	}
	return (res);
}

static t_proj	project_roof_floor(t_proj res, t_sector sector, t_hit hit,
t_ph physic)
{
	res.h_proj.fl_id = translate_in(PART_FLOOR, MOD_NO, sector.sector_id, 0);
	res.h_proj.cl_id = translate_in(PART_CEILING, MOD_NO, sector.sector_id, 0);
	res.h_proj.ray = hit.ray;
	res.h_proj.z_axis = physic.look_v;
	res.h_proj.pos = vec2_to_fvec2(vec3_to_vec2(physic.pos));
	res.h_proj.ceiling = *sector.ceiling_mat;
	res.h_proj.floor = *sector.floor_mat;
	return (res);
}

static t_proj	project_wall(t_proj res, t_sector sector, t_fvec2 top_bot,
t_hit hit)
{
	res.top = (f_from_int(HEIGHT) >> 1) + top_bot.u;
	res.bot = (f_from_int(HEIGHT) >> 1) + top_bot.v;
	res.w_proj.tex_y_iter = f_div(f_from_int(1) << Y_PRECISION, res.bot -\
		res.top);
	res.w_proj.tex_x = hit.t;
	res.top = f_to_int(res.top);
	res.bot = f_to_int(res.bot);
	res.w_proj.wall = *res.tex_proj.wall.mat;
	res.w_proj.id = translate_in(PART_WALL, MOD_NO, hit.wall, 0);
	return (res);
}

t_proj			projection(t_ph physic, t_hit hit, t_sector sector[2],
t_game game)
{
	t_proj		res;
	t_fvec2		h[2];
	t_fvec2		top_bot;

	res.not_found = 0;
	hit.u = (hit.u > 100) ? hit.u : 100;
	res.tex_proj.wall = game.walls[hit.wall];
	res.tex_proj.sector = sector[0];
	h[0] = (t_fvec2) {
		f_from_float((physic.pos.z + physic.height) - sector[0].floor),
		f_from_float((physic.pos.z + physic.height) - sector[0].ceiling)};
	h[1] = (t_fvec2) {
		f_from_float((physic.pos.z + physic.height) - sector[1].floor),
		f_from_float((physic.pos.z + physic.height) - sector[1].ceiling)};
	res.ceil = 0;
	res.step = 0;
	top_bot.u = f_div(RATIO * h[0].v, hit.u) + physic.look_v * 100;
	top_bot.v = f_div(RATIO * h[0].u, hit.u) + physic.look_v * 100;
	res = project_portal(res, top_bot, h, hit);
	res = project_roof_floor(res, sector[0], hit, physic);
	res.h_proj.h = h[0];
	res = project_wall(res, sector[0], top_bot, hit);
	res.id_buf = game.id_buf;
	return (res);
}
