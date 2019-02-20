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

#include <load_save.h>

static t_c_player	translate_player(t_player player)
{
	t_c_player	res;

	res.spawn.gravity = f_from_float(player.spawn.gravity);
	res.spawn.height = f_from_float(player.spawn.height);
	res.spawn.pos = vec3_to_fvec3(player.spawn.pos);
	res.spawn.speed_max = vec3_to_fvec3(player.spawn.speed_max);
	//res.physic.look = vec2_to_fvec2(player.physic.look);
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

static void			write_textures(int fd, t_img *textures, size_t ntextures,\
int index)
{
	t_c_img	ftextures;
	size_t	i;
	size_t	loc_content;

	i = 0;
	loc_content = 0;
	while (i < ntextures)
	{
		ftextures.magic = TEXT_MAGIC + i;
		ftextures.width = textures[i].width;
		ftextures.height = textures[i].height;
		if (i == 0)
			loc_content = (size_t)index;
		else
			loc_content += (size_t)(textures[i - 1].width *
				textures[i - 1].height) * sizeof(t_color);
		ftextures.content = loc_content;
		i++;
		write_struct(&ftextures, fd, sizeof(t_c_img));
	}
}

static t_c_game		save_entities(t_c_game to_save, t_game game)
{
	to_save.nmaterials = game.nmaterials;
	to_save.loc_mats = sizeof(t_c_game);
	to_save.npoints = game.npoints;
	to_save.loc_points = to_save.loc_mats + sizeof(t_c_mat) * game.nmaterials;
	to_save.nwalls = game.nwalls;
	to_save.loc_walls = to_save.loc_points + sizeof(t_c_point) * game.npoints;
	to_save.nsectors = game.nsectors;
	to_save.loc_sectors = to_save.loc_walls + sizeof(t_c_wall) * game.nwalls;
	to_save.nportals = game.nportals;
	to_save.loc_portals = to_save.loc_sectors + sizeof(t_c_sector) *\
		game.nsectors;
	to_save.ntextures = game.ntextures;
	to_save.loc_textures = to_save.loc_portals + sizeof(t_c_portal) *\
		game.nportals;
	to_save.player = translate_player(game.player);
	return (to_save);
}

void				save(const char *filename, t_game game)
{
	t_c_game	to_save;
	int			fd;
	size_t		i;
	int			loc_imgs;

	i = 0;
	to_save.magic = GAME_MAGIC;
	to_save = save_entities(to_save, game);
	fd = open_file(filename, 1, NULL);
	write_struct(&to_save, fd, sizeof(t_c_game));
	write_mats(fd, game.materials, game.nmaterials, game.textures);
	write_points(fd, game.points, game.npoints);
	write_walls(fd, game.walls, game.nwalls, game.materials);
	write_sectors(fd, game.sectors, game.nsectors, game.materials);
	write_portals(fd, game.portals, game.nportals);
	loc_imgs = to_save.loc_textures + sizeof(t_c_img) * game.ntextures;
	write_textures(fd, game.textures, game.ntextures, loc_imgs);
	while (i < to_save.ntextures)
	{
		write(fd, game.textures[i].content, sizeof(t_color) * \
		game.textures[i].height * game.textures[i].width);
		i++;
	}
	console_log("FileLoader3030", "Successfully saved file.");
	close(fd);
}
