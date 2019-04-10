/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:24:11 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/07 14:45:48 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game			create_wall(size_t uwall, size_t sector, t_game game)
{
	const size_t	id = game.sectors[sector].start;
	const t_wall	new_wall = game.walls[game.nwalls + uwall];
	
	game.walls = array_open_swap(game.walls,
		id, game.nwalls + uwall, sizeof(t_wall));
	game.walls[id] = new_wall;
	game.nwalls++;
	game.nuwalls--;
	game = new_update_sectors((ssize_t)(id), -1, -1, game);
	game = new_update_portals(-1, (ssize_t)(id), -1, game);
	return (game);
}
