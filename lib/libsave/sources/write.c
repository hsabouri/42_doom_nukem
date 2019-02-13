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

t_c_player	translate_player(t_player player)
{
	t_c_player	res;

	res.spawn.gravity = f_from_float(player.physic.gravity);
	res.spawn.height = f_from_float(player.physic.height);
	res.spawn.pos = vec3_to_fvec3(player.physic.pos);
	res.spawn.speed_max = vec3_to_fvec3(player.physic.pos);
	//res.physic.look = vec2_to_fvec2(player.physic.look);
	return (res);
}

void		write_struct(void *struc, int fd, size_t size)
{
	if (write(fd, struc, size) < 0)
	{
		close(fd);
		console_error("FileLoader3030", "File saving failed.");
		perror_quit();
	}
}

void		write_points(int fd, t_vec2 *points, size_t npoints)
{
	t_c_point	fpoints;
	size_t		i;

	i = 0;
	while (i < npoints)
	{
		fpoints.magic = POINT_MAGIC + i; 
		fpoints.point = vec2_to_fvec2(points[i]);
		write_struct(&fpoints, fd, sizeof(t_c_point));
		i++;
	}
}

void		save(const char *filename, t_game game)
{
	t_c_game	to_save;
	int			fd;

	to_save.magic = GAME_MAGIC;
	to_save.player = translate_player(game.player);
	to_save.points = sizeof(t_c_game);
	to_save.npoints	= game.npoints;
	to_save.sectors = 0;
	to_save.nsectors = 0;
	to_save.walls = 0;
	to_save.nwalls = 0;
	to_save.portals = 0;
	to_save.nportals = 0;
	fd = open_file(filename, 1, NULL);
	write_struct(&to_save, fd, sizeof(t_c_game));
	write_points(fd, game.points, game.npoints);
	console_log("FileLoader3030", "Successfully saved file.");
	close(fd);
}
