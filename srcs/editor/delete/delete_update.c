/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:51:53 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/06 12:00:13 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game	del_update_portals(ssize_t pts, ssize_t wall, ssize_t sector,
ssize_t mat, t_game game)
{
	size_t		i;
	t_portal	curr;

	i = 0;
	while (i < game.nportals)
	{
		curr = game.portals[i];
		if ((wall >= 0 && (wall == curr.from_wall || wall == curr.to_wall)) ||\
		(sector >= 0 && (sector == curr.from_sector || sector == curr.to_sector)))
			game = delete_portal(i--, game);
		else
		{
			if (pts >= 0 && curr.a > pts)
				curr.a--;
			if (pts >= 0 && curr.b > pts)
				curr.b--;
			if (wall >= 0 && curr.from_wall > wall)
				curr.from_wall--;
			if (wall >= 0 && curr.to_wall > wall)
				curr.to_wall--;
			if (sector >= 0 && curr.from_sector > sector)
				curr.from_sector--;
			if (sector >= 0 && curr.to_sector > sector)
				curr.to_sector--;
			if (mat >= 0 && &game.materials[mat] == curr.mat)
				curr.mat = game.materials;
			if (mat >= 0 && &game.materials[mat] > curr.mat)
				curr.mat = curr.mat - sizeof(t_mat);
			game.portals[i] = curr;
		}
		i++;
	}
	return (game);
}

t_game	del_update_walls(ssize_t pts, ssize_t portal, ssize_t mat, t_game game)
{
	size_t	i;
	t_wall	curr;

	i = 0;
	while (i < game.nwalls)
	{
		curr = game.walls[i];
		if (pts >= 0 && (curr.a == (size_t)pts || curr.b == (size_t)pts))
			game = delete_wall(i--, game);
		else
		{
			if (pts >= 0 && curr.a > pts)
				curr.a--;
			if (pts >= 0 && curr.b > pts)
				curr.b--;
			if (portal >= 0 && curr.portal == portal)
				curr.portal = -1;
			else if (portal >= 0 && curr.portal > portal)
				curr.portal--;
			if (mat >= 0 && &game.materials[mat] == curr.mat)
				curr.mat = game.materials;
			if (mat >= 0 && &game.materials[mat] > curr.mat)
				curr.mat = curr.mat - sizeof(t_mat);
			game.walls[i] = curr;
		}
		i++;
	}
	return (game);
}

t_game	del_update_sectors(ssize_t wall, ssize_t mat, ssize_t sector,\
t_game game)
{
	size_t		i;
	t_sector	curr;

	i = 0;
	while (i < game.nsectors)
	{
		curr = game.sectors[i];
		if (curr.number == 1 && wall >= 0 &&\
		curr.start + curr.number >= wall && curr.start <= wall)
			game = delete_sector(i--, game);
		else
		{
			if (wall >= 0 && curr.start + curr.number > wall &&\
			curr.start <= wall)
				curr.number--;
			if (wall >= 0 && curr.start > wall)
				curr.start--;
			if (sector >= 0 && curr.sector_id > (size_t)sector)
				curr.sector_id--;
			if (mat >= 0 && curr.floor_mat == &game.materials[mat])
				curr.floor_mat = &game.materials[0];
			else if (mat >= 0 && curr.floor_mat > &game.materials[mat])
				curr.floor_mat = curr.floor_mat - sizeof(t_mat);
			if (mat >= 0 && curr.ceiling_mat == &game.materials[mat])
				curr.ceiling_mat = &game.materials[0];
			else if (mat >= 0 && curr.ceiling_mat > &game.materials[mat])
				curr.ceiling_mat = curr.ceiling_mat - sizeof(t_mat);
			game.sectors[i] = curr;
		}
		i++;
	}
	return (game);
}
