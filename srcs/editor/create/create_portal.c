/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_portal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:46:50 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/15 15:29:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

static t_game	prepare_walls(ssize_t *wa, ssize_t *wb, t_game game)
{
	if (*wa < 0)
	{
		*wa = *wb;
		*wb = -1;
	}
	if (*wa < 0)
		return (game);
	if (*wb < 0)
	{
		game = create_wall(\
			(ssize_t[2]){game.walls[*wa].a, game.walls[*wa].b}, 1, game);
		*wb = game.nwalls - 1;
	}
	return (game);
}

static size_t	get_sectors(ssize_t wa, ssize_t wb, size_t *from_sector,
const t_game game)
{
	t_sector	c_sect;
	size_t		to_sector;

	*from_sector = 0;
	while (*from_sector < game.nsectors)
	{
		c_sect = game.sectors[*from_sector];
		if (c_sect.start <= wa && c_sect.start + c_sect.number > wa)
			break ;
		*from_sector += 1;
	}
	to_sector = 0;
	while (to_sector < game.nsectors)
	{
		c_sect = game.sectors[to_sector];
		if (c_sect.start <= wb && c_sect.start + c_sect.number > wb)
			break ;
		to_sector++;
	}
	return (to_sector);
}

t_game			create_portal(ssize_t wa, ssize_t wb, t_game game)
{
	size_t		from_sector;
	size_t		to_sector;

	game = prepare_walls(&wa, &wb, game);
	to_sector = get_sectors(wa, wb, &from_sector, game);
	if (from_sector == game.nsectors || to_sector == game.nsectors)
		return (game);
	if ((game.portals = (t_portal *)realloc(game.portals,\
		(game.nportals + 1) * sizeof(t_portal))) == NULL)
	{
		console_error("ALLOCATION", "Allocation error");
		exit(EXIT_FAILURE);
	}
	game.portals[game.nportals] = (t_portal) { from_sector,
		to_sector, wa, wb,
		game.walls[wa].a,
		game.walls[wa].b,
		NULL
	};
	game.walls[wa].portal = game.nportals;
	game.walls[wb].portal = game.nportals;
	game.nportals++;
	return (game);
}
