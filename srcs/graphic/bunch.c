/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:43:39 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/02 14:44:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

t_bunch	build_bunch(t_game game, t_context context, t_limit limit)
{
	t_bunch			ret;
	t_cache_wall	current;
	const t_sector	sector = game.sectors[context.sector.sector_id];
	const t_fvec2	pos = vec2_to_fvec2(vec3_to_vec2(context.physic.pos));
	size_t			i;

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

t_render		build_sections(t_context context, t_bunch bunch,
t_limit limits)
{
	t_cache_wall	current;
	t_section		current_section;
	t_render		render;

	render.nsections = 0;
	while (render.nsections < bunch.nwalls)
	{
		current = bunch.walls[render.nsections];
		current_section.wall = current;
		current_section.start = get_ray_id(take_left(current.a, current.b),
			limits, context, context.left);
		current_section.end = get_ray_id(take_right(current.a, current.b),
			limits, context, context.right);
		render.sections[render.nsections] = current_section;
		++render.nsections;
	}
	return (render);
}

t_render		build_sections_portals(t_game game, t_context context,
t_render render)
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
