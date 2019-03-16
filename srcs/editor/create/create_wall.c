/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:24:11 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/15 18:15:49 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

static ssize_t	get_before(ssize_t pts[2], t_game game)
{
	int		type;
	size_t	i;
	ssize_t before;

	before = -1;
	type = 1;
	i = 0;
	while (i < game.nwalls)
	{
		if (game.walls[i].a == pts[0] || game.walls[i].b == pts[0])
		{
			before = (ssize_t)i;
			type = 0;
		}
		if (type != 0 && (game.walls[i].a == pts[1] || game.walls[i].b == pts[1]))
			before = (ssize_t)i;
		i++;
	}
	return (before);
}

static t_game	new_sector_wall(ssize_t pts[2], t_game game)
{
	if ((game.walls = (t_wall *)realloc(game.walls,
		(game.nwalls + 1) * sizeof(t_wall))) == NULL)
	{
		console_error("ALLOCATION", "Allocation error");
		exit(EXIT_FAILURE);
	}
	game.walls[game.nwalls] = (t_wall) {fvec2_new(0, 0),
	-1, (u_int32_t)pts[0], (u_int32_t)pts[1], game.materials};
	game.nwalls++;
	game = create_sector(game.nwalls - 1, 1, game);
	return (game);
}

t_game			create_wall(ssize_t pts[2], int new_sector, t_game game)
{
	const ssize_t	before = (new_sector) ? -1 : get_before(pts, game);

	if (before == -1 || new_sector == 1)
		return (new_sector_wall(pts, game));
	if ((game.walls = array_open(game.walls,
		before + 1, game.nwalls, sizeof(t_wall))) == NULL)
	{
		console_error("ALLOCATION", "Allocation error");
		exit(EXIT_FAILURE);
	}
	game.walls[before + 1] = (t_wall) {fvec2_new(0, 0),
		-1, (u_int32_t)pts[0], (u_int32_t)pts[1], game.materials};
	game.nwalls++;
	game = new_update_sectors((ssize_t)(before + 1), -1, -1, game);
	game = new_update_portals(-1, (ssize_t)(before + 1), -1, game);
	return (game);
}
