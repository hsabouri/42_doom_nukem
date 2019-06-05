/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:43:39 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 16:43:33 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include <doom.h>
#include "srcs/graphic/multi_sprite.h"
#include "./singletons.h"

static t_cache_wall	compute_current(t_bunch_compute b, t_cache_wall c)
{
	if (c.portal != -1)
	{
		if (find_wall_order(b.game, b.i) < 2)
		{
			c.left_p = b.game.points[b.game.walls[
				find_wall_portal(b.game, b.i)].a];
			c.right_p = b.game.points[b.game.walls[
				find_wall_portal(b.game, b.i)].b];
		}
		c = switch_portals(c, b.game,
			find_wall_portal(b.game, b.i));
	}
	return (c);
}

static void			compute_bunch(t_bunch_compute b)
{
	t_cache_wall	c;

	c.a = fvec2_sub(vec2_to_fvec2(b.game.points[b.game.walls[b.i].a]), b.pos);
	c.b = fvec2_sub(vec2_to_fvec2(b.game.points[b.game.walls[b.i].b]), b.pos);
	if ((size_t)b.context.mask != b.i && is_in_limit(b.limit, c.a, c.b))
	{
		c.id = b.i;
		c.size = f_from_float(1 / vec2_inv_size(vec2_sub(b.game.points[
			b.game.walls[b.i].b], b.game.points[b.game.walls[b.i].a])));
		c.portal = b.game.walls[b.i].portal;
		c.tex_pos = b.game.walls[b.i].tex_pos;
		c.open = (c.portal >= 0) ? b.game.portals[c.portal].mat : NULL;
		c.mat = *b.game.walls[b.i].mat;
		c.left_z = b.game.points[b.game.walls[b.i].a];
		c.right_z = b.game.points[b.game.walls[b.i].b];
		c = compute_current(b, c);
		c = switch_points(c, b.game, b.i, b.context);
		b.walls[*b.nwalls] = c;
		++(*b.nwalls);
	}
}

t_bunch				build_bunch(const t_game game, const t_context context,
const t_limit limit)
{
	t_bunch			ret;
	const t_sector	sector = game.sectors[context.sector.sector_id];
	const t_fvec2	pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	size_t			i;
	t_cache_wall	walls[NCACHEWALL];

	ret = build_entity_bunch(game, context, limit, pos);
	ret.nwalls = 0;
	i = sector.start;
	while (i < sector.start + sector.number)
	{
		compute_bunch((t_bunch_compute){game, context, limit, walls, pos, i,
			&ret.nwalls});
		++i;
	}
	if (ret.nwalls)
	{
		ret.walls = (t_cache_wall *)safe_malloc(ret.nwalls *
			sizeof(t_cache_wall), "render");
		ft_memmove(ret.walls, walls, ret.nwalls * sizeof(t_cache_wall));
	}
	else
		ret.walls = NULL;
	return (ret);
}

t_render			build_sections(const t_context ctx, const t_bunch b,
const t_limit limits)
{
	t_cache_wall	c;
	t_section		cs;
	t_section		sections[NCACHEWALL];
	t_render		r;

	r = build_sections_entities(ctx, b, limits);
	r.nsections = 0;
	while (r.nsections < b.nwalls)
	{
		c = b.walls[r.nsections];
		cs.wall = c;
		cs.start = get_ray_id(take_left(c.a, c.b), limits, ctx, ctx.left);
		cs.end = get_ray_id(take_right(c.a, c.b), limits, ctx, ctx.right);
		sections[r.nsections] = cs;
		++r.nsections;
	}
	if (r.nsections)
	{
		r.sections = (t_section *)safe_malloc(r.nsections
			* sizeof(t_section), "ring");
		ft_memmove(r.sections, sections, r.nsections * sizeof(t_section));
	}
	else
		r.sections = NULL;
	return (r);
}

t_render			build_sections_portals(t_render render)
{
	t_section	portals[NCACHEWALL];
	int			i;

	i = 0;
	render.nportals = 0;
	while (i < render.nsections)
	{
		if (render.sections[i].wall.portal >= 0)
		{
			portals[render.nportals] = render.sections[i];
			++render.nportals;
		}
		++i;
	}
	if (render.nportals)
	{
		render.portals = (t_section *)safe_malloc(render.nsections
			* sizeof(t_section), "rendering");
		ft_memmove(render.portals, portals, render.nportals
			* sizeof(t_section));
	}
	else
		render.portals = NULL;
	return (render);
}
