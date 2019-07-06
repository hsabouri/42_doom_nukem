/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:42:54 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/06 14:48:55 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <graphic.h>
#include "srcs/common/translate_id.h"

static t_proj	projection(const t_hit hit, const t_context context, t_fvec2 h,
const t_section section)
{
	t_proj	res;
	int		span;
	t_fixed	ratio;

	ratio = f_div(f_from_int(section.id), f_from_int(WIDTH));
	res.bot = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.u, hit.ratios.v)
		+ context.physic.look_v * 100);
	res.top = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.v, hit.ratios.v)
		+ context.physic.look_v * 100);
	res.u = hit.ratios.u;
	res.x = f_mul(section.wall.size, hit.ratios.u) + section.wall.tex_pos.u;
	span = res.bot - res.top;
	res.dis = hit.ratios.v;
	res.y_start = section.wall.tex_pos.v * 200;
	res.y_iter = ((h.u - h.v) << W_PRECISION) / (span + !span);
	res.plane.uid_floor = translate_in(PART_FLOOR, MOD_NO,
		context.sector.sector_id, 0);
	res.plane.uid_roof = translate_in(PART_CEILING, MOD_NO,
		context.sector.sector_id, 0);
	res.plane.h = h;
	res.plane.pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	res.plane.ray = hit.ray;
	res = projection2(context, res, h);
	res.plane = find_line(res.plane.center, res.plane, ratio);
	return (res);
}

t_proj			skybox(t_proj res, int id, const t_context context)
{
	res.tex_wall.x = -context.physic.look_h * RATIO + id;
	res.tex_wall.angle = f_to_int(context.physic.look_v * 100);
	res.plane.tex_roof.x = res.tex_wall.x;
	res.plane.tex_roof.angle = res.tex_wall.angle;
	res.plane.tex_floor.x = res.tex_wall.x;
	res.plane.tex_floor.angle = res.tex_wall.angle;
	return (res);
}

t_proj			wall_projection(int id, t_hit hit, const t_context context,
	t_section section)
{
	t_proj	res;
	t_fvec2	h;

	section.id = id;
	h = proj_h(hit.ratios.u, context.sector, section.wall, context.physic);
	res = projection(hit, context, h, section);
	res = skybox(res, id, context);
	res.uid = translate_in(PART_WALL, MOD_NO, section.wall.id, 0);
	res.is_portal_tex = 0;
	res.plane.tex_roof.mat = *context.sector.ceiling_mat;
	res.plane.tex_floor.mat = *context.sector.floor_mat;
	res.tex_wall.mat = section.wall.mat;
	res.tex_wall.ambient = context.sector.ambient;
	res.plane.tex_floor.ambient = context.sector.ambient;
	res.plane.tex_roof.ambient = context.sector.ambient;
	return (res);
}

t_proj			portal_projection(int id, t_hit hit, const t_context context,
	t_section section)
{
	t_proj		res;
	t_fvec2		h;
	t_fvec2		h2;

	section.id = id;
	h = proj_h(hit.ratios.u, context.sector, section.wall, context.physic);
	h2 = proj_hp(hit.ratios.u, section.next, section.wall, context.physic);
	res = projection(hit, context, h, section);
	res = skybox(res, id, context);
	res.uid = translate_in(PART_PORTAL, MOD_OPEN, section.wall.id, 0);
	res.uid_step = translate_in(PART_PORTAL, MOD_STEP, section.wall.id, 0);
	res.uid_ceil = translate_in(PART_PORTAL, MOD_CEIL, section.wall.id, 0);
	res.step = res.bot + f_to_int(f_div(RATIO * (h2.u - h.u), hit.ratios.v));
	res.ceil = res.top + f_to_int(f_div(RATIO * (h2.v - h.v), hit.ratios.v));
	res.plane.tex_roof.mat = *context.sector.ceiling_mat;
	res.plane.tex_floor.mat = *context.sector.floor_mat;
	res.tex_open = res.tex_wall;
	res.is_portal_tex = 0;
	if (section.wall.open)
	{
		res.is_portal_tex = 1;
		res.tex_open.mat = *section.wall.open;
	}
	res.tex_wall.mat = section.wall.mat;
	return (res);
}

t_e_proj		entity_projection(t_hit hit, const t_context context,
	const t_section_entity section)
{
	t_e_proj	res;
	t_fvec2		h;
	t_fvec2		sector_h;
	int			span;

	h.u = f_from_float((context.physic.pos.z + context.physic.height))
	- section.entity.h;
	h.v = h.u - f_from_float(section.entity.physic.height);
	sector_h.u = f_from_float((context.physic.pos.z + context.physic.height)
	- context.sector.floor.z);
	sector_h.v = f_from_float((context.physic.pos.z + context.physic.height)
	- context.sector.ceiling.z);
	res.bot = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.u, hit.ratios.v)
	+ context.physic.look_v * 100);
	res.top = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.v, hit.ratios.v)
	+ context.physic.look_v * 100);
	span = res.bot - res.top;
	if (h.u > sector_h.u)
		res.bot = (HEIGHT >> 1) + f_to_int(f_div(RATIO * sector_h.u,
			hit.ratios.v) + context.physic.look_v * 100);
	res.uid = translate_in(PART_ENTITY, MOD_NO, section.entity.id, 0);
	res.mat = *section.entity.mat;
	res.y_iter = f_from_int(1 << E_PRECISION) / (span + !span);
	res.dis = hit.ratios.v;
	return (res);
}
