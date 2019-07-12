/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 13:46:22 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/11 10:33:46 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void			*dump_struct(void *buf, size_t start, size_t size, size_t max)
{
	if (start + size <= max)
		return (buf + start);
	else
	{
		console_error("FileLoader3030", "File corrupted\
			(error no. 0xbalkaNES)");
		exit(EXIT_FAILURE);
	}
	return (NULL);
}

void			verify_magic(void *t_c_struct, size_t magic, size_t index)
{
	if (*(size_t *)t_c_struct != magic + index)
	{
		console_error("FileLoader3030", "File corrupted\
			(error no. 0xbalkaMNI)");
		exit(EXIT_FAILURE);
	}
}

static t_game	parse_2(void *buf, t_c_game game, t_save save, t_game res)
{
	res.nportals = game.nportals;
	save.index = game.loc_entities;
	res.entities = parse_entities(buf, save, res.multi_mats, game.nentities);
	res.nentities = game.nentities;
	res.unique_e_id = game.unique_e_id;
	save.index = game.loc_player;
	res.player = parse_player(game, res, buf, save);
	return (res);
}

static t_game	parse_1(void *buf, t_c_game game, t_save save)
{
	t_game res;

	save.index = game.loc_textures;
	res.textures = parse_textures(buf, save, game.ntextures);
	res.ntextures = game.ntextures;
	save.index = game.loc_mats;
	res.materials = parse_mats(buf, save, res.textures, game.nmaterials);
	res.nmaterials = game.nmaterials;
	res.multi_mats = init_multi_sprite(&res, res.materials);
	res.classes = init_classe(&res, res.multi_mats);
	save.index = game.loc_points;
	res.points = parse_points(buf, save, game.npoints);
	res.npoints = game.npoints;
	save.index = game.loc_walls;
	res.walls = parse_walls(buf, save, res.materials, game.nwalls);
	res.nwalls = game.nwalls;
	res.nuwalls = 0;
	save.index = game.loc_sectors;
	res.sectors = parse_sectors(buf, save, res.materials, game.nsectors);
	res.nsectors = game.nsectors;
	save.index = game.loc_portals;
	res.portals = parse_portals(buf, save, game.nportals, res.materials);
	return (res);
}

t_game			*load(const char *filename, int edit_mode)
{
	void		*buf;
	size_t		max;
	t_c_game	game;
	t_game		*res;
	t_save		save;

	res = NULL;
	if (!(buf = dump_file(filename, edit_mode, &max)))
		return (NULL);
	game = *(t_c_game *)dump_struct(buf, 0, sizeof(t_c_game), max);
	verify_magic(&game, GAME_MAGIC, 0);
	save.max = max;
	res = (t_game *)safe_malloc(sizeof(t_game), "loader");
	*res = parse_1(buf, game, save);
	*res = parse_2(buf, game, save, *res);
	fix_fly(res->entities, res->nentities, res->sectors);
	free(buf);
	return (res);
}
