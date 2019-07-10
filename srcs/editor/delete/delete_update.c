/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:51:53 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/10 13:50:40 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game	del_update_portals(ssize_t wall, ssize_t sector, t_game game)
{
	size_t		i;
	t_portal	curr;

	i = -1;
	while (++i < game.nportals)
	{
		curr = game.portals[i];
		if ((wall >= 0 && (wall == curr.from_wall || wall == curr.to_wall))
		|| (sector >= 0 && (sector == curr.from_sector
		|| sector == curr.to_sector)))
			game = delete_portal(i--, game);
		else
		{
			if (wall >= 0 && curr.from_wall > wall)
				curr.from_wall--;
			if (wall >= 0 && curr.to_wall > wall)
				curr.to_wall--;
			if (sector >= 0 && curr.from_sector > sector)
				curr.from_sector--;
			if (sector >= 0 && curr.to_sector > sector)
				curr.to_sector--;
			game.portals[i] = curr;
		}
	}
	return (game);
}

t_game	del_update_walls(ssize_t pts, ssize_t portal, t_game game)
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
			game.walls[i] = curr;
		}
		i++;
	}
	return (game);
}

t_game	del_update_sectors(ssize_t wall, ssize_t sector, t_game game)
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
			game.sectors[i] = curr;
		}
		i++;
	}
	return (game);
}

t_game	del_update_inventory(ssize_t entity, t_game game)
{
	t_array		new_inventory;
	size_t		i;
	size_t		*curr;

	new_inventory = safe_anew(NULL, game.player.inventory.len, sizeof(size_t),
		"renew inventory");
	i = 0;
	while ((curr = (size_t *)anth(&game.player.inventory, i)))
	{
		if (*curr < (size_t)entity)
			apush(&new_inventory, curr);
		else if (*curr > (size_t)entity)
		{
			*curr -= 1;
			apush(&new_inventory, curr);
		}
		i++;
	}
	if (game.player.inventory.mem)
		free(game.player.inventory.mem);
	game.player.inventory = new_inventory;
	return (game);
}

t_game	del_update_entities(ssize_t sector, t_game game)
{
	size_t		i;
	t_entity	curr;

	i = 0;
	while (i < game.nentities)
	{
		curr = game.entities[i];
		if (curr.spawn.sector_id == sector)
			game = delete_entity(i--, game);
		else
		{
			if (curr.spawn.sector_id > sector)
				curr.spawn.sector_id--;
			curr.physic = curr.spawn;
			game.entities[i] = curr;
		}
		i++;
	}
	return (game);
}
