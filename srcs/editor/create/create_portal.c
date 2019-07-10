/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_portal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:46:50 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/22 18:02:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

static t_game	prepare_walls(t_game game, ssize_t wa, ssize_t wb)
{
	const t_wall	a = game.walls[wa];
	const t_wall	b = game.walls[wb];
	const t_vec2	diff_a = vec2_sub(game.points[a.a], game.points[b.a]);
	const t_vec2	diff_b = vec2_sub(game.points[a.b], game.points[b.b]);
	size_t			tmp;

	if (!vec2_equal(diff_a, diff_b, 0.001))
	{
		tmp = game.walls[wb].a;
		game.walls[wb].a = game.walls[wb].b;
		game.walls[wb].b = tmp;
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

static t_game	equalize_sectors(size_t from_sector, size_t to_sector,
t_game game)
{
	game.sectors[to_sector].ceiling = game.sectors[from_sector].ceiling;
	game.sectors[to_sector].ceiling_b = game.sectors[from_sector].ceiling;
	game.sectors[to_sector].floor = game.sectors[from_sector].floor;
	game.sectors[to_sector].floor_b = game.sectors[from_sector].floor;
	return (game);
}

t_game			create_portal(ssize_t wa, ssize_t wb, t_game game, int equalize)
{
	size_t		from_sector;
	size_t		to_sector;

	game = prepare_walls(game, wa, wb);
	to_sector = get_sectors(wa, wb, &from_sector, game);
	if (from_sector == game.nsectors || to_sector == game.nsectors)
		return (game);
	if ((game.portals = (t_portal *)realloc(game.portals,\
		(game.nportals + 1) * sizeof(t_portal))) == NULL)
	{
		console_error("ALLOCATION", "Allocation error");
		exit(EXIT_FAILURE);
	}
	if (equalize)
		game = equalize_sectors(from_sector, to_sector, game);
	game.portals[game.nportals] = (t_portal) {from_sector, to_sector, wa, wb,
		NULL, 0};
	game.walls[wa].portal = game.nportals;
	game.walls[wb].portal = game.nportals;
	game.nportals++;
	return (game);
}
