/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 11:36:35 by hugo              #+#    #+#             */
/*   Updated: 2019/01/23 13:33:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_c_player	translate_player(t_player player)
{
	t_c_player	res;

	res.spawn.gravity = f_from_float(player.spawn.gravity);
	res.spawn.height = f_from_float(player.spawn.height);
	res.spawn.radius = f_from_float(player.spawn.radius);
	res.spawn.pos = vec3_to_fvec3(player.spawn.pos);
	res.spawn.speed_max = vec3_to_fvec3(player.spawn.speed_max);
	res.spawn.look.u = f_from_float(player.physic.look_h);
	res.spawn.look.v = player.spawn.look_v;
	res.spawn.sector_id = player.spawn.sector_id;
	return (res);
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
	game_s.nmaterials = game.nmaterials;
	game_s.loc_mats = sizeof(t_c_game);
	game_s.npoints = game.npoints;
	game_s.loc_points = game_s.loc_mats + sizeof(t_c_mat) * game.nmaterials;
	game_s.nwalls = game.nwalls;
	game_s.loc_walls = game_s.loc_points + sizeof(t_c_point) * game.npoints;
	game_s.nsectors = game.nsectors;
	game_s.loc_sectors = game_s.loc_walls + sizeof(t_c_wall) * game.nwalls;
	game_s.nportals = game.nportals;
	game_s.loc_portals = game_s.loc_sectors + sizeof(t_c_sector) *\
		game.nsectors;
	game_s.nentities = game.nentities;
	game_s.loc_entities = game_s.loc_portals + sizeof(t_c_portal) *\
		game.nportals;
	game_s.ntextures = game.ntextures;
	game_s.loc_textures = game_s.loc_entities + sizeof(t_c_entity) *\
		game.nentities;
	game_s.nmusic = game.music.len;
	game_s.loc_music = game_s.loc_textures + sizeof(t_c_img) *\
		game.ntextures;
	game_s.nsounds = game.sounds.len;
	game_s.loc_sounds = game_s.loc_music + sizeof(t_c_music) *\
		game.music.len;
	game_s.player = translate_player(game.player);
	return (game_s);
}

static void			write_map(int fd, t_c_game game_save, t_game game)
{
	size_t	loc_imgs;
	size_t	loc_music;
	size_t	loc_sound;

	write_mats(fd, game.materials, game.nmaterials, game.textures);
	write_points(fd, game.points, game.npoints);
	write_walls(fd, game.walls, game.nwalls, game.materials);
	write_sectors(fd, game.sectors, game.nsectors, game.materials);
	write_portals(fd, game.portals, game.nportals);
	translate_entity(fd, game.entities, game.nentities, game.materials);
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
