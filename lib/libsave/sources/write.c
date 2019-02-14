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

void	write_walls(int fd, t_wall *walls, size_t nwalls)
{
	t_c_wall	fwalls;
	size_t		i;
	
	i = 0;
	while (i < nwalls)
	{
		fwalls.magic = WALL_MAGIC + i;
		fwalls.portal = walls[i].portal;
		fwalls.a = walls[i].a;
		fwalls.b = walls[i].b;
		fwalls.mat = 0;
		write_struct(&fwalls, fd, sizeof(t_c_wall));
		i++;
	}
}

void		write_sectors(int fd, t_sector *sectors, size_t nsectors)
{
	t_c_sector	fsectors;
	size_t		i;

	i = 0;
	while (i < nsectors)
	{
		fsectors.magic = SECTOR_MAGIC + i;
		fsectors.start = sectors[i].start;
		fsectors.number = sectors[i].number;
		fsectors.sector_id = sectors[i].sector_id;
		fsectors.floor = f_from_float(sectors[i].floor);
		fsectors.ceiling = f_from_float(sectors[i].ceiling);
		fsectors.ambient = sectors[i].ambient;
		fsectors.ceiling_mat = 0;
		fsectors.floor_mat = 0;
		write_struct(&fsectors, fd, sizeof(t_c_sector));
		i++;
	}
}

void		write_portals(int fd, t_portal *portals, size_t nportals)
{
	t_c_portal	fportals;
	size_t		i;

	i = 0;
	while (i < nportals)
	{
		fportals.magic = PORTAL_MAGIC + i;
		fportals.from_sector = portals[i].from_sector;
		fportals.to_sector = portals[i].to_sector;
		fportals.from_wall = portals[i].from_wall;
		fportals.to_wall = portals[i].to_wall;
		fportals.a = portals[i].a;
		fportals.b = portals[i].b;
		write_struct(&fportals, fd, sizeof(t_c_portal));
		i++;
	}
}

void		save(const char *filename, t_game game)
{
	t_c_game	to_save;
	int			fd;

	to_save.magic = GAME_MAGIC;
	to_save.player = translate_player(game.player);
	to_save.npoints	= game.npoints;
	to_save.nwalls = game.nwalls;
	to_save.nsectors = game.nsectors;
	to_save.nportals = game.nportals;
	fd = open_file(filename, 1, NULL);
	write_struct(&to_save, fd, sizeof(t_c_game));
	write_points(fd, game.points, game.npoints);
	write_walls(fd, game.walls, game.nwalls);
	write_sectors(fd, game.sectors, game.nsectors);
	write_portals(fd, game.portals, game.nportals);
	console_log("FileLoader3030", "Successfully saved file.");
	close(fd);
}
