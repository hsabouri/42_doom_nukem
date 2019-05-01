/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 13:46:22 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/26 13:55:48 by lbougero         ###   ########.fr       */
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
	t_player	current;
	t_c_player  struc_p;
	t_mat		*mat;
	size_t		j;

	struc_p = *(t_c_player *)dump_struct(buf, save.index, sizeof(t_c_player), save.max);
	verify_magic(&struc_p, PLAYER_MAGIC, 0);
	current = player_default();
	current.my_entity.physic.gravity = f_to_float(struc_p.my_entity.spawn.gravity);
	current.my_entity.physic.height = f_to_float(struc_p.my_entity.spawn.height);
	current.my_entity.physic.radius = f_to_float(struc_p.my_entity.spawn.radius);
	current.my_entity.physic.rad_inter = f_to_float(struc_p.my_entity.spawn.rad_inter);
	current.my_entity.physic.pos = fvec3_to_vec3(struc_p.my_entity.spawn.pos);
	current.my_entity.physic.speed_max = fvec3_to_vec3(struc_p.my_entity.spawn.speed_max);
	current.my_entity.physic.look_v = struc_p.my_entity.spawn.look.v;
	current.my_entity.physic.look_h = f_to_float(struc_p.my_entity.spawn.look.u);
	if (current.my_entity.physic.look_h > M_PI / 2 && current.my_entity.physic.look_h < -M_PI / 2)
		current.my_entity.physic.look_h = 0;
	current.my_entity.physic.sector_id = struc_p.my_entity.spawn.sector_id;
	current.my_entity.mat = safe_anew(NULL, 1, sizeof(t_mat *), "loader");
	j = 0;
	while (j < 16)
	{
		mat = (struc_p.my_entity.mat[j] == -1) ? NULL : 
			id_to_p(struc_p.my_entity.mat[j], new_game.materials, sizeof(t_mat));
		if (!mat)
			break;
		else
			apush(&current.my_entity.mat, &mat);
		j++;
	}
	current.life = struc_p.life;
	current.weapons[0] = struc_p.weapons[0];
	current.weapons[1] = struc_p.weapons[1];
	current.secondary = struc_p.secondary;
	current.equiped = struc_p.equiped;
	save.index = game.loc_inventory;
	current.inventory = parse_inventory(buf, save, new_game.entities,
		game.ninventory);
	current.my_entity.damage = struc_p.my_entity.damage;
	res = current;
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
	save.index = game.loc_player;
	res.player = parse_player(game, res, buf, save);
	save.index = game.loc_events;
	res.waiting_events = parse_events(buf, save, game.nevents, res,
		res.player);
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
		res = generate_map();
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
		res.log = safe_anew(NULL, 100, sizeof(t_trigger), "loader");
		// debug(res);
	}
	return (res);
}
