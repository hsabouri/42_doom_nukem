/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 13:46:22 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/23 13:34:23 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <load_save.h>

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

t_entity		*parse_entities(void *buf, t_save save, t_mat *mats,\
size_t n_entities)
{
	t_c_entity	struc_e;
	t_entity	*entities;
	t_entity	current;
	size_t		i;

	entities = (t_entity *)malloc(sizeof(t_entity) * n_entities);
	i = 0;
	while (i < n_entities)
	{
		struc_e = *(t_c_entity *)dump_struct(buf, save.index +
			sizeof(t_c_entity) * i, sizeof(t_c_entity), save.max);
		verify_magic(&struc_e, ENTITY_MAGIC, i);
		current = entity_default();
		current.physic.gravity = f_to_float(struc_e.spawn.gravity);
		current.physic.height = f_to_float(struc_e.spawn.height);
		current.physic.radius = f_to_float(struc_e.spawn.radius);
		current.physic.pos = fvec3_to_vec3(struc_e.spawn.pos);
		current.physic.speed_max = fvec3_to_vec3(struc_e.spawn.speed_max);
		current.physic.look_v = struc_e.spawn.look.v;
		current.physic.look_h = f_to_float(struc_e.spawn.look.u);
		if (current.physic.look_h > M_PI / 2 && current.physic.look_h < -M_PI / 2)
			current.physic.look_h = 0;
		current.physic.sector_id = struc_e.spawn.sector_id;
		current.mat = id_to_p((ssize_t)struc_e.mat, mats, sizeof(t_mat));
		current.damage = struc_e.damage;
		entities[i] = current;
		i++;
	}
	return (entities);
}

t_player		parse_player(t_c_player player)
{
	t_player	res;

	res = player_default();
	res.physic.gravity = f_to_float(player.spawn.gravity);
	res.physic.height = f_to_float(player.spawn.height);
	res.physic.radius = f_to_float(player.spawn.radius);
	res.physic.pos = fvec3_to_vec3(player.spawn.pos);
	res.physic.speed_max = fvec3_to_vec3(player.spawn.speed_max);
	res.physic.look_v = player.spawn.look.v;
	res.physic.look_h = f_to_float(player.spawn.look.u);
	if (res.physic.look_h > M_PI / 2 && res.physic.look_h < -M_PI / 2)
		res.physic.look_h = 0;
	res.physic.sector_id = player.spawn.sector_id;
	return (res);
}

static t_game	parse_1(void *buf, t_game res, t_c_game game, t_save save)
{
	res.player = parse_player(game.player);
	save.index = game.loc_textures;
	res.textures = parse_textures(buf, save, game.ntextures);
	res.ntextures = game.ntextures;
	save.index = game.loc_mats;
	res.materials = parse_mats(buf, save, res.textures, game.nmaterials);
	res.nmaterials = game.nmaterials;
	save.index = game.loc_points;
	res.points = parse_points(buf, save, game.npoints);
	res.npoints = game.npoints;
	save.index = game.loc_walls;
	res.walls = parse_walls(buf, save, res.materials, game.nwalls);
	res.nwalls = game.nwalls;
	save.index = game.loc_sectors;
	res.sectors = parse_sectors(buf, save, res.materials, game.nsectors);
	res.nsectors = game.nsectors;
	save.index = game.loc_portals;
	res.portals = parse_portals(buf, save, game.nportals);
	res.nportals = game.nportals;
	save.index = game.loc_entities;
	res.entities = parse_entities(buf, save, res.materials, game.nentities);
	res.nentities = game.nentities;
	return (res);
}

t_game			load(const char *filename)
{
	void		*buf;
	size_t		max;
	t_c_game	game;
	t_game		res;
	t_save		save;

	buf = dump_file(filename, 0, &max);
	game = *(t_c_game *)dump_struct(buf, 0, sizeof(t_c_game), max);
	verify_magic(&game, GAME_MAGIC, 0);
	save.max = max;
	res = parse_1(buf, res, game, save);
	// debug(res);
	return (res);
}
