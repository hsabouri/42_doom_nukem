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

void		write_mats(int fd, t_mat *mats, size_t nmats)
{
	t_c_mat		fmats;
	size_t	i;

	i = 0;
	while (i < nmats)
	{
		fmats.magic = MAT_MAGIC + i;
		fmats.pos.u = mats[i].pos.u;
		fmats.pos.v = mats[i].pos.v;
		fmats.sca.u = mats[i].sca.u;
		fmats.sca.v = mats[i].sca.v;
		fmats.color = mats[i].color;
		fmats.texture = NULL; // a voir apres save/load texture;
		fmats.mode = mats[i].mode;
		fmats.filter = mats[i].filter;
		if (mats[i].overlay != NULL)
			fmats.overlay = id_from_p(mats[i].overlay, mats, sizeof(t_mat));
		else
			fmats.overlay = -1;
		write_struct(&fmats, fd, sizeof(t_c_mat));
		i++;
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

void	write_walls(int fd, t_wall *walls, size_t nwalls, t_mat	*mats)
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
		fwalls.mat = id_from_p(walls[i].mat, mats, sizeof(t_mat));
		write_struct(&fwalls, fd, sizeof(t_c_wall));
		i++;
	}
}

void		write_sectors(int fd, t_sector *sectors, size_t nsectors, t_mat *mats)
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
		fsectors.ceiling_mat = id_from_p(sectors[i].ceiling_mat, mats, sizeof(t_mat));
		fsectors.floor_mat = id_from_p(sectors[i].floor_mat, mats, sizeof(t_mat));
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
	to_save.nmaterials = game.nmaterials;
	to_save.npoints	= game.npoints;
	to_save.nwalls = game.nwalls;
	to_save.nsectors = game.nsectors;
	to_save.nportals = game.nportals;
	fd = open_file(filename, 1, NULL);
	write_struct(&to_save, fd, sizeof(t_c_game));
	write_mats(fd, game.materials, game.nmaterials);
	write_points(fd, game.points, game.npoints);
	write_walls(fd, game.walls, game.nwalls, game.materials);
	write_sectors(fd, game.sectors, game.nsectors, game.materials);
	write_portals(fd, game.portals, game.nportals);
	console_log("FileLoader3030", "Successfully saved file.");
	close(fd);
}
