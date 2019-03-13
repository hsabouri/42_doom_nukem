/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:46:50 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/11 13:30:13 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game		create_portal(ssize_t wa, ssize_t wb, t_game game)
{
	t_sector	c_sect;
	size_t		from_sector;
	size_t		to_sector;

	if (wa < 0)
	{
		wa = wb;
		wb = -1;
	}
	if (wa < 0)
		return (game);
	if (wb < 0)
	{
		game = create_wall(\
			(ssize_t[2]){game.walls[wa].a, game.walls[wa].b}, 1, game);
		wb = game.nwalls - 1;
	}
	from_sector = 0;
	while (from_sector < game.nsectors)
	{
		c_sect = game.sectors[from_sector];
		if (c_sect.start <= wa &&
			c_sect.start + c_sect.number > wa)
			break ;
		from_sector++;
	}
	to_sector = 0;
	while (to_sector < game.nsectors)
	{
		c_sect = game.sectors[to_sector];
		if (c_sect.start <= wb &&
			c_sect.start + c_sect.number > wb)
			break ;
		to_sector++;
	}
	if (from_sector == game.nsectors || to_sector == game.nsectors)
		return (game);
	if ((game.portals = (t_portal *)realloc(game.portals,\
		(game.nportals + 1) * sizeof(t_portal))) == NULL)
	{
		console_error("ALLOCATION", "Allocation error, realloc returned NULL");
		exit(EXIT_FAILURE);
	}
	game.portals[game.nportals] = (t_portal) {
		from_sector,
		to_sector,
		wa,
		wb,
		game.walls[wa].a,
		game.walls[wa].b,
		NULL
	};
	game.walls[wa].portal = game.nportals;
	game.walls[wb].portal = game.nportals;
	game.nportals++;
	return (game);
}

t_game		create_sector(size_t start, size_t nwalls, t_game game)
{
	game.sectors = (t_sector *)realloc(game.sectors, (game.nsectors + 1)\
		* sizeof(t_sector));
	game.sectors[game.nsectors] = (t_sector) {
		start,
		nwalls,
		game.nsectors,
		-2,
		2,
		WHITE,
		game.materials,
		game.materials,
		fvec2_new(0, 0)
	};
	game.nsectors++;
	return (game);
}

t_game		create_point(t_vec2 pts, t_game game)
{
	game.points = (t_vec2 *)realloc(game.points,\
		(1 + game.npoints) * sizeof(t_vec2));
	game.points[game.npoints] = pts;
	game.npoints++;
	return (game);
}

t_game		create_wall(ssize_t pts[2], int new_sector, t_game game)
{
	size_t	i;
	int		type;
	ssize_t	before;

	i = 0;
	type = 1;
	before = -1;
	while (i < game.nwalls && new_sector == 0)
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
	if (before == -1 || new_sector == 1)
	{
		game.walls = (t_wall *)realloc(game.walls, (game.nwalls + 1) * sizeof(t_wall));
		game.walls[game.nwalls] = (t_wall) {fvec2_new(0, 0),
		-1, (u_int32_t)pts[0], (u_int32_t)pts[1], game.materials};
		game.nwalls++;
		game = create_sector(game.nwalls - 1, 1, game);
		return (game);
	}
	game.walls = array_open(game.walls, before + 1, game.nwalls, sizeof(t_wall));
	game.walls[before + 1] = (t_wall) {fvec2_new(0, 0),
		-1, (u_int32_t)pts[0], (u_int32_t)pts[1], game.materials};
	game.nwalls++;
	game = new_update_sectors((ssize_t)(before + 1), -1, -1, game);
	game = new_update_portals(-1, (ssize_t)(before + 1), -1, game);
	return (game);
}
