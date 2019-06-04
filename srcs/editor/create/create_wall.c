/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:24:11 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/22 14:06:37 by hsabouri         ###   ########.fr       */
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
	new_update_portals(id, -1, game);
	new_update_sectors(id, -1, game);
	return (game);
}
