/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 11:36:35 by hugo              #+#    #+#             */
/*   Updated: 2019/04/26 13:06:33 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void			write_inventory(t_player player, t_entity *entities,\
int fd)
{
	t_entity **entity;
	size_t	index;

	index = 0;
	while ((entity = (t_entity **)ashift(&player.inventory)))
	{
		index = id_from_p(*entity, entities, sizeof(t_entity));
		write_struct(&index, fd, sizeof(size_t));
	}
}

static t_c_player	translate_player(t_player player)
{
	t_c_player	res;
	u_int32_t	index;
	t_mat		**material;
	size_t		j;

	res.magic = PLAYER_MAGIC;
	res.my_entity.spawn.gravity = f_from_float(player.my_entity.spawn.gravity);
	res.my_entity.spawn.height = f_from_float(player.my_entity.spawn.height);
	res.my_entity.spawn.radius = f_from_float(player.my_entity.spawn.radius);
	res.my_entity.spawn.pos = vec3_to_fvec3(player.my_entity.spawn.pos);
	res.my_entity.spawn.speed_max = vec3_to_fvec3(player.my_entity.spawn.speed_max);
	res.my_entity.spawn.look.u = f_from_float(player.my_entity.physic.look_h);
	res.my_entity.spawn.look.v = player.my_entity.spawn.look_v;
	res.my_entity.spawn.sector_id = player.my_entity.spawn.sector_id;
	res.life = player.life;
	res.weapons[0] = player.weapons[0];
	res.weapons[1] = player.weapons[1];
	res.secondary = player.secondary;
	res.equiped = player.equiped;
	j = 0;
	while ((material = (t_mat **)ashift(&player.my_entity.mat)))
	{
		index = id_from_p(*material, mats, sizeof(t_mat));
		res.my_entity.mat[j] = (ssize_t)index;
		j++;
	}
	while (j < 16)
	{
		res.my_entity.mat[j] = -1;
		j++;
	}
	res.my_entity.damage = player.my_entity.damage;
	write_struct(&res, fd, sizeof(t_c_entity));
}

void				write_struct(void *struc, int fd, size_t size)
{
	if (write(fd, struc, size) < 0)
	{
		close(fd);
		console_error("FileLoader3030", "File saving failed.");
		perror_quit();
	}
}

static t_c_game		save_entities(t_c_game game_s, t_game game)
{
	game_s.ninventory = game.player.inventory.len;
	game_s.loc_inventory = sizeof(t_c_game);
	game_s.nmaterials = game.nmaterials;
	game_s.loc_mats = sizeof(t_c_game) + sizeof(size_t) * game_s.ninventory;
	game_s.loc_player = game_s.loc_mats + sizeof(t_c_mat) * game.nmaterials;
	game_s.npoints = game.npoints;
	game_s.loc_points = game_s.loc_player + sizeof(t_c_player);
	game_s.nwalls = game.nwalls;
	game_s.nuwalls = game.nuwalls;
	game_s.loc_walls = game_s.loc_points + sizeof(t_c_point) * game.npoints;
	game_s.nsectors = game.nsectors;
	game_s.loc_sectors = game_s.loc_walls + sizeof(t_c_wall) * game.nwalls;
	game_s.nportals = game.nportals;
	game_s.loc_portals = game_s.loc_sectors + sizeof(t_c_sector)\
		* game.nsectors;
	game_s.nentities = game.nentities;
	game_s.loc_entities = game_s.loc_portals + sizeof(t_c_portal)\
		* game.nportals;
	game_s.nweapons = game.nweapons;
	game_s.loc_weapons = game_s.loc_entities + sizeof(t_c_entity)\
		* game.nentities;
	game_s.ntextures = game.ntextures;
	game_s.loc_textures = game_s.loc_weapons + sizeof(t_c_weapon)\
		* game.nweapons;
	game_s.nmusic = game.music.len;
	game_s.loc_music = game_s.loc_textures + sizeof(t_c_img)\
		* game.ntextures;
	game_s.nsounds = game.sounds.len;
	game_s.loc_sounds = game_s.loc_music + sizeof(t_c_music)\
		* game.music.len;
	game_s.player = translate_player(game.player);
	return (game_s);
}

static void			write_map(int fd, t_c_game game_save, t_game game)
{
	size_t	loc_imgs;
	size_t	loc_music;
	size_t	loc_sound;

	write_inventory(game.player, game.entities,fd);
	write_mats(fd, game.materials, game.nmaterials, game.textures);
	translate_player(game.player, fd, game.materials);
	write_points(fd, game.points, game.npoints);
	write_walls(fd, game.walls, game.nwalls, game.materials);
	write_sectors(fd, game.sectors, game.nsectors, game.materials);
	write_portals(fd, game.portals, game.nportals, game.materials);
	translate_entity(fd, game.entities, game.nentities, game.materials);
	write_weapons(fd, game.weapons, game.nweapons, game.textures);
	loc_imgs = game_save.loc_sounds + sizeof(t_c_music) * game.sounds.len;
	loc_music = write_textures(fd, game.textures, game.ntextures, loc_imgs);
	loc_sound = write_audio(fd, loc_music, MUSIC);
	write_audio(fd, loc_sound, SOUND);
}

void				save(const char *filename, t_game game)
{
	t_c_game	game_save;
	int			fd;
	size_t		size;
	size_t		i;

	i = 0;
	game_save.magic = GAME_MAGIC;
	game_save = save_entities(game_save, game);
	fd = open_file(filename, 1, &size);
	write_struct(&game_save, fd, sizeof(t_c_game));
	write_map(fd, game_save, game);
	while (i < game_save.ntextures)
	{
		write(fd, game.textures[i].content, sizeof(t_color) * \
		game.textures[i].height * game.textures[i].width);
		i++;
	}
	write_music(fd, MUSIC);
	write_music(fd, SOUND);
	console_log("FileLoader3030", "Successfully saved file.");
	close(fd);
}
