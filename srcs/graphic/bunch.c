/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:43:39 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/05 12:57:23 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

t_bunch	build_entity_bunch(t_game game, t_context context, t_limit limit,
t_fvec2 pos)
{
	t_bunch			ret;
	t_cache_entity	current;
	const size_t	sector = context.sector.sector_id;
	size_t			i;
	t_fvec2			tmp;

	i = -1;
	ret.nentities = 0;
	while (++i != (size_t)-1 && i < game.nentities)
		if (game.entities[i].physic.sector_id == sector)
		{
			tmp = vec2_to_fvec2(vec2_rot(vec2_new(game.entities[i].w / 2, 0), context.physic.look_h));
			current.a = fvec2_sub(vec2_to_fvec2(vec3_to_vec2(game.entities[i].physic.pos)), pos);
			current.b = fvec2_add(current.a, tmp);
			current.a = fvec2_sub(current.a, tmp);
			if (is_in_limit(limit, context, take_left(current.a, current.b),
				take_right(current.a, current.b), i))
			{
				current.id = i;
				current.h = f_from_float(game.entities[i].physic.pos.z);
				current.physic = game.entities[i].physic;
				current.mat = *game.entities[i].mat;
				ret.entities[ret.nentities] = current;
				++ret.nentities;
			}
		}
	return (ret);
}

t_bunch	build_bunch(t_game game, t_context context, t_limit limit)
{
	t_bunch			ret;
	t_cache_wall	current;
	const t_sector	sector = game.sectors[context.sector.sector_id];
	const t_fvec2	pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	size_t			i;

	ret = build_entity_bunch(game, context, limit, pos);
	ret.nwalls = 0;
	i = sector.start;
	while (i < sector.start + sector.number)
	{
		current.a = fvec2_sub(vec2_to_fvec2(game.points[game.walls[i].a]), pos);
		current.b = fvec2_sub(vec2_to_fvec2(game.points[game.walls[i].b]), pos);
		if ((size_t)context.mask != i &&
			is_in_limit(limit, context, current.a, current.b, i))
		{
			current.id = i;
			current.portal = game.walls[i].portal;
			current.mat = *game.walls[i].mat;
			ret.walls[ret.nwalls] = current;
			++ret.nwalls;
		}
		++i;
	}
	return (ret);
}

t_render		build_sections_entities(t_context context, t_bunch bunch, t_limit limits)
{
	t_cache_entity		current;
	t_section_entity	current_section;
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
		render.entities[render.nentities] = current_section;
		++render.nentities;
	}
	return (render);
}

t_render		build_sections(t_context context, t_bunch bunch,
t_limit limits)
{
	t_cache_wall	current;
	t_section		current_section;
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
			limits, context, context.right - 1);
		render.sections[render.nsections] = current_section;
		++render.nsections;
	}
	return (render);
}

t_render		build_sections_portals(t_render render)
{
	int	i;

	i = 0;
	render.nportals = 0;
	while (i < render.nsections)
	{
		if (render.sections[i].wall.portal >= 0)
		{
			render.portals[render.nportals] = render.sections[i];
			++render.nportals;
		}
		++i;
	}
	return (render);
}
