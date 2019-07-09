/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:34:53 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/21 12:51:00 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game	delete_portal(size_t portal, t_game game)
{
	if (!(game.portals =\
	array_close(game.portals, portal, game.nportals, sizeof(t_portal))))
		return (game);
	game.nportals--;
	game = del_update_walls(-1, (ssize_t)portal, game);
	return (game);
}

t_game	delete_sector(size_t sector, t_game game)
{
	if (!(game.sectors =\
	array_close(game.sectors, sector, game.nsectors, sizeof(t_sector))))
		return (game);
	game.nsectors--;
	game = del_update_portals(-1, sector, game);
	game = del_update_sectors(-1, sector, game);
	game = del_update_entities(sector, game);
	return (game);
}

t_game	delete_wall(size_t wall, t_game game)
{
	if (!(game.walls =\
	array_close(game.walls, wall, game.nwalls + game.nuwalls, sizeof(t_wall))))
		return (game);
	game.nwalls--;
	game = del_update_portals(wall, -1, game);
	game = del_update_sectors(wall, -1, game);
	return (game);
}

t_game	delete_point(size_t point, t_game game)
{
	if (!(game.points =\
	array_close(game.points, point, game.npoints, sizeof(t_vec2))))
		return (game);
	game.npoints--;
	return (del_update_walls(point, -1, game));
}

t_game	delete_entity(size_t entity, t_game game)
{
	if (entity >= game.nentities)
		return (game);
	if (!(game.entities =\
	array_close(game.entities, entity, game.nentities, sizeof(t_entity))))
		return (game);
	game = del_update_inventory(entity, game);
	game.nentities--;
	return (game);
}
