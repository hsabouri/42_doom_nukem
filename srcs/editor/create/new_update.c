/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:51:53 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/21 12:43:06 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game	new_update_portals(ssize_t wall, ssize_t sector, t_game game)
{
	t_portal	curr;
	size_t		i;

	i = 0;
	while (i < game.nportals)
	{
		curr = game.portals[i];
		if (wall >= 0 && curr.from_wall >= wall)
			curr.from_wall++;
		if (wall >= 0 && curr.to_wall >= wall)
			curr.to_wall++;
		if (sector >= 0 && curr.from_sector >= sector)
			curr.from_sector++;
		if (sector >= 0 && curr.from_sector >= sector)
			curr.from_sector++;
		game.portals[i] = curr;
		i++;
	}
	return (game);
}

t_game	new_update_walls(ssize_t point, ssize_t portal, t_game game)
{
	t_wall	curr;
	size_t	i;

	i = 0;
	while (i < game.nwalls)
	{
		curr = game.walls[i];
		if (point >= 0 && curr.a >= point)
			curr.a++;
		if (point >= 0 && curr.b >= point)
			curr.b++;
		if (portal >= 0 && curr.portal >= portal)
			curr.portal++;
		game.walls[i] = curr;
		i++;
	}
	return (game);
}

t_game	new_update_sectors(ssize_t wall, ssize_t sector, t_game game)
{
	t_sector	curr;
	size_t		i;

	i = 0;
	while (i < game.nsectors)
	{
		curr = game.sectors[i];
		if (wall >= 0 && curr.start > (u_int32_t)wall)
			curr.start++;
		if (wall >= 0 && curr.start == (u_int32_t)wall)
			curr.number++;
		if (sector >= 0 && curr.sector_id >= (size_t)sector)
			curr.sector_id++;
		game.sectors[i] = curr;
		i++;
	}
	return (game);
}
