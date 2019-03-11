/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 13:46:22 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/26 12:02:52 by lbougero         ###   ########.fr       */
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

t_array			parse_inventory(void *buf, t_save save, t_entity *entities,\
size_t n_inventory)
{
	t_array		res;
	size_t		index;
	t_entity	*entity;
	size_t		i;

	res = safe_anew(NULL, 1, sizeof(t_entity *), "loader");
	i = 0;
	while (i < n_inventory)
	{
		index = *(size_t *)dump_struct(buf, save.index + sizeof(size_t) * i,
			sizeof(size_t), save.max);
		entity = id_to_p(index, entities, sizeof(t_entity));
		apush(&res, &entity);
		i++;
	}
	return (res);
}

t_player		parse_player(t_c_game game, t_game new_game, void *buf,\
t_save save)
{
	t_player	res;

	res = player_default();
	res.physic.gravity = f_to_float(game.player.spawn.gravity);
	res.physic.height = f_to_float(game.player.spawn.height);
	res.physic.radius = f_to_float(game.player.spawn.radius);
	res.physic.pos = fvec3_to_vec3(game.player.spawn.pos);
	res.physic.speed_max = fvec3_to_vec3(game.player.spawn.speed_max);
	res.physic.look_v = game.player.spawn.look.v;
	res.physic.look_h = f_to_float(game.player.spawn.look.u);
	if (res.physic.look_h > M_PI / 2 && res.physic.look_h < -M_PI / 2)
		res.physic.look_h = 0;
	res.physic.sector_id = game.player.spawn.sector_id;
	res.life = game.player.life;
	res.weapons[0] = game.player.weapons[0];
	res.weapons[1] = game.player.weapons[1];
	res.secondary = game.player.secondary;
	res.equiped = game.player.equiped;
	res.inventory = parse_inventory(buf, save, new_game.entities,
		game.ninventory);
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
	save.index = game.loc_points;
	res.points = parse_points(buf, save, game.npoints);
	res.npoints = game.npoints;
	save.index = game.loc_walls;
	res.walls = parse_walls(buf, save, res.materials, game.nwalls);
	res.nwalls = game.nwalls;
	res.nuwalls = game.nuwalls;
	save.index = game.loc_sectors;
	res.sectors = parse_sectors(buf, save, res.materials, game.nsectors);
	res.nsectors = game.nsectors;
	save.index = game.loc_portals;
	res.portals = parse_portals(buf, save, game.nportals, res.materials);
	res.nportals = game.nportals;
	save.index = game.loc_entities;
	res.entities = parse_entities(buf, save, res.materials, game.nentities);
	res.nentities = game.nentities;
	save.index = game.loc_weapons;
	res.weapons = parse_weapons(buf, save, res.textures, game.nweapons);
	res.nweapons = game.nweapons;
	save.index = game.loc_inventory;
	res.player = parse_player(game, res, buf, save);
	return (res);
}

t_game			load(const char *filename, int edit_mode)
{
	void		*buf;
	size_t		max;
	t_c_game	game;
	t_game		res;
	t_save		save;

	if (!(buf = dump_file(filename, edit_mode, &max)))
		res = default_map();
	else
	{
		game = *(t_c_game *)dump_struct(buf, 0, sizeof(t_c_game), max);
		verify_magic(&game, GAME_MAGIC, 0);
		save.max = max;
		res = parse_1(buf, game, save);
		save.index = game.loc_music;
		parse_audio(buf, save, game.nmusic, MUSIC);
		save.index = game.loc_sounds;
		parse_audio(buf, save, game.nsounds, SOUND);
		// debug(res);
	}
	return (res);
}
