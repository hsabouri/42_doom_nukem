/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:51:35 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/03 13:36:55 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

inline t_sector	teleport_sector(t_game game, t_context context,
	t_section section)
{
	if (game.portals[section.wall.portal].from_sector
	== context.sector.sector_id)
		return (game.sectors[game.portals[section.wall.portal].to_sector]);
	else
		return (game.sectors[game.portals[section.wall.portal].from_sector]);
}

t_context		teleport(t_game game, t_context context, t_section section)
{
	t_wall			to_wall;
	t_wall			from_wall;
	const t_portal	portal = game.portals[section.wall.portal];

	context.left = section.start;
	context.right = section.end;
	if (portal.from_wall == section.wall.id)
	{
		context.sector = game.sectors[portal.to_sector];
		context.mask = portal.to_wall;
		from_wall = game.walls[portal.from_wall];
		to_wall = game.walls[portal.to_wall];
	}
	else
	{
		context.sector = game.sectors[portal.from_sector];
		context.mask = portal.from_wall;
		from_wall = game.walls[portal.to_wall];
		to_wall = game.walls[portal.from_wall];
	}
	context.physic.pos.x += game.points[to_wall.a].u
		- game.points[from_wall.a].u;
	context.physic.pos.y += game.points[to_wall.a].v
		- game.points[from_wall.a].v;
	return (context);
}
