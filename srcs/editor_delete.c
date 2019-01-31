/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:34:53 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/28 16:07:30 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	delete_portal(size_t portal, t_game game)
{
	if (!(game.portals =\
	array_close(game.portals, portal, game.nportals, sizeof(t_portal))))
		return (game);
	game.nportals--;
	return (game);
}

t_game	delete_sector(size_t sector, t_game game)
{
	if (!(game.sectors =\
	array_close(game.sectors, sector, game.nsectors, sizeof(t_sector))))
		return (game);
	game.nsectors--;
	game = del_update_portals(-1, sector, game);
	game = del_update_sectors(-1, -1, sector, game);
	return (game);
}

t_game	delete_wall(size_t wall, t_game game)
{
	if (!(game.walls =\
	array_close(game.walls, wall, game.nwalls, sizeof(t_wall))))
		return (game);
	game.nwalls--;
	game = del_update_portals(wall, -1, game);
	game = del_update_sectors(wall, -1, -1, game);
	return (game);
}

t_game	delete_point(size_t point, t_game game)
{
	if (!(game.points =\
	array_close(game.points, point, game.npoints, sizeof(t_vec2))))
		return (game);
	game.npoints--;
	return (del_update_walls(point, -1, -1, game));
}
