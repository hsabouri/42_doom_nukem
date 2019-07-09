/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 11:36:35 by hugo              #+#    #+#             */
/*   Updated: 2019/07/09 13:05:22 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void			write_struct(void *struc, int fd, size_t size)
{
	if (write(fd, struc, size) < 0)
	{
		close(fd);
		console_error("FileLoader3030", "File saving failed.");
		perror_quit();
	}
}

static t_c_game	save_game(t_c_game game_s, t_game game)
{
	game_s.loc_player = sizeof(t_c_game);
	game_s.nmaterials = game.nmaterials;
	game_s.loc_mats = game_s.loc_player + sizeof(t_c_player);
	game_s.npoints = game.npoints;
	game_s.loc_points = game_s.loc_mats + sizeof(t_c_mat) * game.nmaterials;
	game_s.nwalls = game.nwalls;
	game_s.nuwalls = game.nuwalls;
	game_s.loc_walls = game_s.loc_points + sizeof(t_c_point) * game.npoints;
	game_s.nsectors = game.nsectors;
	game_s.loc_sectors = game_s.loc_walls + sizeof(t_c_wall) * game.nwalls;
	game_s.nportals = game.nportals;
	game_s.loc_portals = game_s.loc_sectors + sizeof(t_c_sector)
		* game.nsectors;
	game_s.nentities = game.nentities;
	game_s.loc_entities = game_s.loc_portals + sizeof(t_c_portal)
		* game.nportals;
	game_s.unique_e_id = game.unique_e_id;
	game_s.ntextures = game.ntextures;
	game_s.loc_textures = game_s.loc_entities + sizeof(t_c_entity)
		* game.nentities;
	return (game_s);
}

static void		write_map(int fd, t_c_game game_save, t_game game)
{
	size_t	loc_imgs;

	write_player(game.player, fd, game.multi_mats);
	write_mats(fd, game.materials, game.nmaterials, game.textures);
	write_points(fd, game.points, game.npoints);
	write_walls(fd, game.walls, game.nwalls, game.materials);
	write_sectors(fd, game.sectors, game.nsectors, game.materials);
	write_portals(fd, game.portals, game.nportals, game.materials);
	write_entities(fd, game.entities, game.nentities, game.multi_mats);
	loc_imgs = game_save.loc_textures + sizeof(t_c_img) * game.ntextures;
	write_textures(fd, game.textures, game.ntextures, loc_imgs);
}

void			save(const char *filename, t_game game)
{
	t_c_game	game_save;
	int			fd;
	size_t		size;
	size_t		i;

	i = 0;
	game_save.magic = GAME_MAGIC;
	game_save = save_game(game_save, game);
	fd = open_file(filename, 1, &size);
	write_struct(&game_save, fd, sizeof(t_c_game));
	write_map(fd, game_save, game);
	while (i < game_save.ntextures)
	{
		write(fd, game.textures[i].content, sizeof(t_color) *
		game.textures[i].height * game.textures[i].width);
		i++;
	}
	console_log("FileLoader3030", "Successfully saved file.");
	close(fd);
}
