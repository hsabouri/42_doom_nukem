/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:05:59 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/24 15:01:53 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static int	verify_height(t_game game, t_sector sector, float floor,\
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
			if (adj_sector.floor >= ceiling || adj_sector.ceiling <= floor)
				return (0);
		}
		i++;
	}
	return (1);
}

t_sector	sector_height(t_game game, t_sector sector, t_part part, float add)
{
	if (part == PART_FLOOR &&\
	verify_height(game, sector, sector.floor + add, sector.ceiling))
		sector.floor += add;
	else if (part == PART_CEILING &&\
	verify_height(game, sector, sector.floor, sector.ceiling + add))
		sector.ceiling += add;
	return (sector);
}
