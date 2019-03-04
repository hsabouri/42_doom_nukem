/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:42:54 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/04 14:01:21 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>


static t_proj	projection(t_hit hit, t_context context, t_fvec2 h)
{
	t_proj	res;
	int			span;

	res.bot = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.u, hit.ratios.v) +
		context.physic.look_v * 100);
	res.top = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.v, hit.ratios.v) +
		context.physic.look_v * 100);
	res.u = hit.ratios.u;
	res.x = hit.ratios.u;
	span = res.bot - res.top;
	res.y_iter = f_from_int(1 << 8) / (span + !span);
	res.plane.h = h;
	res.plane.pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	res.plane.ray = hit.ray;
	res.plane.wr.u = f_div(-h.v, f_mul((f_from_int(HEIGHT) / WIDTH),
		f_from_float(PWIDTH)));
	res.plane.wr.v = f_div(-h.u, f_mul((f_from_int(HEIGHT) / WIDTH),
		f_from_float(PWIDTH)));
	res.plane.look_v = f_to_int(context.physic.look_v * 100);
	return (res);
}

t_proj			wall_projection(int id, t_hit hit, t_context context,
t_section section)
{
	t_proj res;
	t_fvec2		h;

	if (hit.ratios.v < 10)
		hit.ratios.v = 10;
	h.u = f_from_float((context.physic.pos.z + context.physic.height) -
		context.sector.floor);
	h.v = f_from_float((context.physic.pos.z + context.physic.height) -
		context.sector.ceiling);
	res = projection(hit, context, h);
	res.is_portal = 0;
	res.plane.mat_ceiling = *context.sector.ceiling_mat;
	res.plane.mat_floor = *context.sector.floor_mat;
	res.mat_wall = section.wall.mat;
	res.tex.ambient = context.sector.ambient;
	res.id = id;
	return (res);
}

t_proj			portal_projection(int id, t_hit hit, t_context context,
t_section section)
{
	t_proj		res;
	t_fvec2			h;
	t_fvec2			h2;


	if (hit.ratios.v < 10)
		hit.ratios.v = 10;
	h.u = f_from_float((context.physic.pos.z + context.physic.height) -
		context.sector.floor);
	h.v = f_from_float((context.physic.pos.z + context.physic.height) -
		context.sector.ceiling);
	h2.u = f_from_float((context.physic.pos.z + context.physic.height) -
		section.next.floor);
	h2.v = f_from_float((context.physic.pos.z + context.physic.height) -
		section.next.ceiling);
	res = projection(hit, context, h);
	res.is_portal = 1;
	res.step = res.bot + f_to_int(f_div(RATIO * (h2.u - h.u), hit.ratios.v));
	res.ceil = res.top + f_to_int(f_div(RATIO * (h2.v - h.v), hit.ratios.v));
	res.plane.mat_ceiling = *context.sector.ceiling_mat;
	res.plane.mat_floor = *context.sector.floor_mat;
	res.mat_wall = section.wall.mat;
	res.tex.ambient = context.sector.ambient;
	res.id = id;
	return (res);
}

t_e_proj		entity_projection(int id, t_hit hit, t_context context,
t_section_entity section)
{
	t_e_proj	res;
	t_fvec2		h;
	int			span;

	h.u = f_from_float((context.physic.pos.z + context.physic.height) -
		section.entity.h);
	h.v = f_from_float((context.physic.pos.z + context.physic.height) -
		(section.entity.h + 1)); // replace by height of entity
	res.bot = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.u, hit.ratios.v) +
		context.physic.look_v * 100);
	res.top = (HEIGHT >> 1) + f_to_int(f_div(RATIO * h.v, hit.ratios.v) +
		context.physic.look_v * 100);
	res.mat = section.entity.mat;
	span = res.bot - res.top;
	res.u = hit.ratios.u;
	res.x = hit.ratios.u;
	res.tex.ambient = context.sector.ambient;
	res.y_iter = f_from_int(1 << 8) / (span + !span);
	return (res);
}