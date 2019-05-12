/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:43:39 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/12 15:09:22 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include <doom.h>
#include "srcs/graphic/multi_sprite.h"

t_bunch	build_entity_bunch(const t_game game, const t_context context,
const t_limit limit, t_fvec2 pos)
{
	t_bunch			ret;
	t_cache_entity	current;
	const size_t	sector = context.sector.sector_id;
	size_t			i;
	t_fvec2			tmp;

	t_cache_entity	entities[NCACHEENTITY];

	i = -1;
	ret.nentities = 0;
	while (++i != (size_t)-1 && i < game.nentities)
	{
		if (game.entities[i].physic.sector_id == sector)
		{
			tmp = vec2_to_fvec2(vec2_rot(vec2_new(game.entities[i].physic.radius, 0), context.physic.look_h));
			current.a = fvec2_sub(vec2_to_fvec2(vec3_to_vec2(game.entities[i].physic.pos)), pos);
			current.dis = fvec2_ssize(current.a);
			current.b = fvec2_add(current.a, tmp);
			current.a = fvec2_sub(current.a, tmp);
			if (is_in_limit(limit, take_left(current.a, current.b),
				take_right(current.a, current.b)))
			{
				current.id = i;
				current.h = f_from_float(game.entities[i].physic.pos.z);
				current.physic = game.entities[i].physic;
				current.mat = choose_entity_material(game.entities[i], vec3_to_vec2(context.physic.pos));
				entities[ret.nentities] = current;
				++ret.nentities;
			}
		}
	}
	if (ret.nentities)
	{
		ret.entities = (t_cache_entity *)safe_malloc(ret.nentities * sizeof(t_cache_entity), "rendering");
		memmove(ret.entities, entities, ret.nentities * sizeof(t_cache_entity));
	}
	else
		ret.entities = NULL;
	return (ret);
}

t_bunch	build_bunch(const t_game game, const t_context context,
const t_limit limit)
{
	t_bunch			ret;
	t_cache_wall	current;
	const t_sector	sector = game.sectors[context.sector.sector_id];
	const t_fvec2	pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	size_t			i;

	t_cache_wall	walls[NCACHEWALL];

	ret = build_entity_bunch(game, context, limit, pos);
	ret.nwalls = 0;
	i = sector.start;
	while (i < sector.start + sector.number)
	{
		current.a = fvec2_sub(vec2_to_fvec2(game.points[game.walls[i].a]), pos);
		current.b = fvec2_sub(vec2_to_fvec2(game.points[game.walls[i].b]), pos);
		if ((size_t)context.mask != i &&
			is_in_limit(limit, current.a, current.b))
		{
			current.id = i;
			current.size = f_from_float(1 / vec2_inv_size(vec2_sub(
				game.points[game.walls[i].b], game.points[game.walls[i].a])));
			current.portal = game.walls[i].portal;
			current.tex_pos = game.walls[i].tex_pos;
			current.open = (current.portal >= 0) ? game.portals[current.portal].mat : NULL;
			current.mat = *game.walls[i].mat;
			current.left_z = game.points[game.walls[i].a];
			current.right_z = game.points[game.walls[i].b];
			current = switch_points(current,game,i);
			walls[ret.nwalls] = current;
			++ret.nwalls;
		}
		++i;
	}
	if (ret.nwalls)
	{
		ret.walls = (t_cache_wall *)safe_malloc(ret.nwalls * sizeof(t_cache_wall), "rendering");
		memmove(ret.walls, walls, ret.nwalls * sizeof(t_cache_wall));
	}
	else
		ret.walls = NULL;
	return (ret);
}

t_render		build_sections_entities(const t_context context, const t_bunch bunch, const t_limit limits)
{
	t_cache_entity		current;
	t_section_entity	current_section;
	t_section_entity	entities[NCACHEENTITY];
	t_render			render;

	render.nentities = 0;
	while (render.nentities < bunch.nentities)
	{
		current = bunch.entities[render.nentities];
		current_section.entity = current;
		current_section.start = get_ray_id(
			take_left(current.a, current.b), limits, context, context.left);
		current_section.end = get_ray_id(
			take_right(current.a, current.b), limits, context, context.right);
		entities[render.nentities] = current_section;
		++render.nentities;
	}
	if (render.nentities)
	{
		render.entities = (t_section_entity *)safe_malloc(render.nentities * sizeof(t_section_entity), "rendering");
		memmove(render.entities, entities, render.nentities * sizeof(t_section_entity));
	}
	else
		render.entities = NULL;
	return (render);
}

t_render		build_sections(const t_context context, const t_bunch bunch, const t_limit limits)
{
	t_cache_wall	current;
	t_section		current_section;
	t_section		sections[NCACHEWALL];
	t_render		render;

	render = build_sections_entities(context, bunch, limits);
	render.nsections = 0;
	while (render.nsections < bunch.nwalls)
	{
		current = bunch.walls[render.nsections];
		current_section.wall = current;
		current_section.start = get_ray_id(take_left(current.a, current.b),
			limits, context, context.left);
		current_section.end = get_ray_id(take_right(current.a, current.b),
			limits, context, context.right);
		sections[render.nsections] = current_section;
		++render.nsections;
	}
	if (render.nsections)
	{
		render.sections = (t_section *)safe_malloc(render.nsections * sizeof(t_section), "rendering");
		memmove(render.sections, sections, render.nsections * sizeof(t_section));
	}
	else
		render.sections = NULL;
	return (render);
}

t_render		build_sections_portals(t_render render)
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
		render.portals = (t_section *)safe_malloc(render.nsections * sizeof(t_section), "rendering");
		memmove(render.portals, portals, render.nportals * sizeof(t_section));
	}
	else
		render.portals = NULL;
	return (render);
}
