/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:42:54 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/31 14:18:54 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <graphic.h>
#include "srcs/common/translate_id.h"

static t_proj	projection(const t_hit hit, const t_context context, t_fvec2 h, const t_section section, int id)
{
	t_proj	res;
	int		span;
	t_fixed ratio;

	ratio = f_div(f_from_int(id),f_from_int(WIDTH));
	res.bot = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.u, hit.ratios.v) +
		context.physic.look_v * 100);
	res.top = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.v, hit.ratios.v) +
		context.physic.look_v * 100);
	res.u = hit.ratios.u;
	res.x = f_mul(section.wall.size, hit.ratios.u) + section.wall.tex_pos.u;
	span = res.bot - res.top;
	res.y_start = section.wall.tex_pos.v * 200;
	res.y_iter = ((h.u - h.v) << 9) / (span + !span);
	res.plane.uid_floor = translate_in(PART_FLOOR, MOD_NO, context.sector.sector_id, 0);
	res.plane.uid_roof = translate_in(PART_CEILING, MOD_NO, context.sector.sector_id, 0);
	res.plane.h = h;
	res.plane.pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	res.plane.ray = hit.ray;
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
	res.plane.line.z.u =  (res.plane.height);
	res.plane = find_line(res.plane.center, res.plane,ratio,context.sector);
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
	t_fixed	dis;
	t_fixed	dis2;

	dis = find_z(context.sector, section.wall.left_z, 1) - find_z(context.sector, section.wall.right_z, 1);
	dis = f_mul(dis, hit.ratios.u);
	dis2 = find_z(context.sector, section.wall.left_z, 0) - find_z(context.sector, section.wall.right_z, 0);
	dis2 = f_mul(dis2, hit.ratios.u);
	h.u = f_from_float((context.physic.pos.z + context.physic.height)) - find_z(context.sector, section.wall.left_z, 1) + dis;
	h.v = f_from_float((context.physic.pos.z + context.physic.height)) - find_z(context.sector, section.wall.left_z, 0) + dis2;
	if (hit.ratios.v < 10)
		hit.ratios.v = 10;
	res = projection(hit, context, h, section, id);
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
	t_fvec2			h;
	t_fvec2			h2;
	t_wall			wall;

	if (hit.ratios.v < 10)
		hit.ratios.v = 10;
		t_fixed	dis;
		t_fixed	dis2;

	dis = find_z(context.sector, section.wall.left_z, 1) - find_z(context.sector, section.wall.right_z, 1);
	dis = f_mul(dis, hit.ratios.u);
	dis2 = find_z(context.sector, section.wall.left_z, 0) - find_z(context.sector, section.wall.right_z, 0);
	dis2 = f_mul(dis2, hit.ratios.u);
	h.u = f_from_float((context.physic.pos.z + context.physic.height)) - find_z(context.sector, section.wall.left_z, 1) + dis;
	h.v = f_from_float((context.physic.pos.z + context.physic.height)) - find_z(context.sector, section.wall.left_z, 0) + dis2;
	dis = find_z(section.next, section.wall.left_p, 1) - find_z(section.next, section.wall.right_p, 1);
	dis = f_mul(dis, hit.ratios.u);
	dis2 = find_z(section.next, section.wall.left_p, 0) - find_z(section.next, section.wall.right_p, 0);
	dis2 = f_mul(dis2, hit.ratios.u);
	// h2.u = f_from_float((context2.physic.pos.z + context2.physic.height)) - find_z(section.next, section.wall.left_z, 1) + dis;
	// h2.v = f_from_float((context2.physic.pos.z + context2.physic.height)) - find_z(section.next, section.wall.left_z, 0) + dis2;
	h2.u = f_from_float((context.physic.pos.z + context.physic.height)) - find_z(section.next, section.wall.right_p, 1) + dis;
	h2.v = f_from_float((context.physic.pos.z + context.physic.height)) - find_z(section.next, section.wall.right_p, 0) + dis2;
	res = projection(hit, context, h, section, id);
	res = skybox(res, id, context);
	res.uid = translate_in(PART_PORTAL, MOD_OPEN, section.wall.id, 0);
	res.uid_step = translate_in(PART_PORTAL, MOD_STEP, section.wall.id, 0);
	res.uid_ceil = translate_in(PART_PORTAL, MOD_CEIL, section.wall.id, 0);
	res.step = res.bot + f_to_int(f_div(RATIO * (h2.u - h.u), hit.ratios.v));
	res.ceil = res.top + f_to_int(f_div(RATIO * (h2.v - h.v), hit.ratios.v));
	res.plane.tex_roof.mat = *context.sector.ceiling_mat;
	res.plane.tex_floor.mat = *context.sector.floor_mat;
	res.tex_open = res.tex_wall;
	if (section.wall.open)
	{
		res.is_portal_tex = 1;
		res.tex_open.mat = *section.wall.open;
	}
	else
		res.is_portal_tex = 0;
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

	if (hit.ratios.v < 10)
		hit.ratios.v = 10;
	h.u = f_from_float((context.physic.pos.z + context.physic.height)) -
		section.entity.h;
	h.v = h.u - f_from_float(section.entity.physic.height);
	sector_h.u = f_from_float((context.physic.pos.z + context.physic.height) -
		context.sector.floor.z);
	sector_h.v = f_from_float((context.physic.pos.z + context.physic.height) -
		context.sector.ceiling.z);
	res.bot = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.u, hit.ratios.v) +
		context.physic.look_v * 100);
	res.top = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.v, hit.ratios.v) +
		context.physic.look_v * 100);
	span = res.bot - res.top;
	if (h.u > sector_h.u)
		res.bot = (HEIGHT >> 1) + f_to_int(f_div(RATIO * sector_h.u, hit.ratios.v) +
		context.physic.look_v * 100);
	res.uid = translate_in(PART_ENTITY, MOD_NO, section.entity.id, 0);
	res.mat = *section.entity.mat;
	res.u = hit.ratios.u;
	res.x = hit.ratios.u;
	res.tex.ambient = context.sector.ambient;
	res.y_iter = f_from_int(1 << 8) / (span + !span);
	return (res);
}
