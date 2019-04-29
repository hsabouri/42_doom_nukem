/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_game_sectors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:05:59 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/15 11:08:34 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

static int		verify_height(t_game game, t_sector sector, float floor,\
float ceiling)
{
	size_t		i;
	t_portal	portal;
	t_sector	adj_sector;

	i = sector.start;
	while (i < sector.number)
	{
		if (game.walls[i].portal >= 0)
		{
			portal = game.portals[game.walls[i].portal];
			adj_sector = (portal.to_sector == sector.sector_id) ?\
				game.sectors[portal.from_sector] :\
				game.sectors[portal.to_sector];
			if (adj_sector.floor.z >= ceiling || adj_sector.ceiling.z <= floor)
				return (0);
		}
		i++;
	}
	return (1);
}

static t_sector	sector_height(t_game game, t_sector sector, t_part part, float add)
{
	if (part == PART_FLOOR &&\
	verify_height(game, sector, sector.floor.z + add, sector.ceiling.z))
		sector.floor.z += add;
	else if (part == PART_CEILING &&\
	verify_height(game, sector, sector.floor.z, sector.ceiling.z + add))
		sector.ceiling.z += add;
	return (sector);
}

t_env			sector_height_tool(t_env env, t_selected selected)
{
	if (selected.type == PART_CEILING && (env.events.keys[SDL_SCANCODE_EQUALS] ||
		env.events.keys[SDL_SCANCODE_KP_PLUS]))
		env.game.sectors[selected.id] = sector_height(env.game,
			env.game.sectors[selected.id], PART_CEILING, 0.1);
	else if (selected.type == PART_CEILING &&
		(env.events.keys[SDL_SCANCODE_MINUS] ||
			env.events.keys[SDL_SCANCODE_KP_MINUS]))
		env.game.sectors[selected.id] = sector_height(env.game,
			env.game.sectors[selected.id], PART_CEILING, -0.1);
	else if (selected.type == PART_FLOOR &&
		(env.events.keys[SDL_SCANCODE_EQUALS] ||
		env.events.keys[SDL_SCANCODE_KP_PLUS]))
			env.game.sectors[selected.id] = sector_height(env.game,
			env.game.sectors[selected.id], PART_FLOOR, 0.1);
	else if (selected.type == PART_FLOOR &&
		(env.events.keys[SDL_SCANCODE_MINUS] ||
		env.events.keys[SDL_SCANCODE_KP_MINUS]))
			env.game.sectors[selected.id] = sector_height(env.game,
			env.game.sectors[selected.id], PART_FLOOR, -0.1);
	return (env);
}
