/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_new_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:51:53 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/09 16:17:41 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game	new_update_portals(ssize_t point, ssize_t wall, ssize_t sector,\
t_game game)
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
		if (point >= 0 && curr.a >= point)
			curr.a++;
		if (point >= 0 && curr.b >= point)
			curr.b++;
		game.portals[i] = curr;
		i++;
	}
	return (game);
}

t_game	new_update_walls(ssize_t point, ssize_t mat, ssize_t portal,\
t_game game)
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
		if (mat >= 0 && curr.mat >= &game.materials[mat])
			curr.mat += sizeof(t_mat);
		game.walls[i] = curr;
		i++;
	}
	return (game);
}

t_game	new_update_sectors(ssize_t wall, ssize_t mat, ssize_t sector,\
t_game game)
{
	t_sector	curr;
	size_t		i;

	i = 0;
	while (i < game.nsectors)
	{
		curr = game.sectors[i];
		if (wall >= 0 && curr.start >= (u_int32_t)wall)
			curr.start++;
		if (wall >= 0 && curr.start + curr.number >= (u_int32_t)wall\
		&& curr.start <= (u_int32_t)wall)
			curr.number++;
		if (mat >= 0 && curr.ceiling_mat >= &game.materials[mat])
			curr.ceiling_mat += sizeof(t_mat);
		if (mat >= 0 && curr.floor_mat >= &game.materials[mat])
			curr.floor_mat += sizeof(t_mat);
		if (sector >= 0 && curr.sector_id >= (size_t)sector)
			curr.sector_id++;
		game.sectors[i] = curr;
		i++;
	}
	return (game);
}
