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

static void	*dump_struct(void *buf, size_t start, size_t size, size_t max)
{
	if (start + size <= max)
		return (buf + start);
	else
	{
		console_error("FileLoader3030", "File corrupted (error no. 0xbalkaNES)");
		exit(EXIT_FAILURE);
	}
	return (NULL);
}

static void	verify_magic(void *t_c_struct, size_t magic, size_t index)
{
	if (*(size_t *)t_c_struct != magic + index)
	{
		console_error("FileLoader3030", "File corrupted (error no. 0xbalkaMNI)");
		exit(EXIT_FAILURE);
	}
}

void		debug(t_game game)
{
	int	i;

	// printf("player.physic.gravity: %f\n", game.player.physic.gravity);
	// printf("player.physic.height: %f\n", game.player.physic.height);
	// printf("player.physic.pos: {%f, %f, %f}\n", game.player.physic.pos.x, game.player.physic.pos.y, game.player.physic.pos.z);
	// printf("player.physic.speed: {%f, %f, %f}\n", game.player.physic.pos.x, game.player.physic.pos.y, game.player.physic.pos.z);
	// printf("player.physic.speed_max: {%f, %f, %f}\n", game.player.physic.speed_max.x, game.player.physic.speed_max.y, game.player.physic.speed_max.z);
	// printf("player.physic.look: {%f, %f}\n", game.player.physic.look.u, game.player.physic.look.v);

	i = 0;
	while (i < (int)game.nportals)
	{
		printf("portal.from_sector: %u, portal.to_sector: %u, portal.from_wall: %u, portal.to_wall: %u, portal.a: %u, portal.b = %u\n", \
		game.portals[i].from_sector, game.portals[i].to_sector, game.portals[i].from_wall, game.portals[i].to_wall, game.portals[i].a, game.portals[i].b);
		i++;
	}
	printf("nportals: %zu\n", game.nportals);
}

t_player	parse_player(t_c_player player)
{
	t_player	res;

	res = player_default();
	res.physic.gravity = f_to_float(player.spawn.gravity);
	res.physic.height = f_to_float(player.spawn.height);
	res.physic.pos = fvec3_to_vec3(player.spawn.pos);
	res.physic.speed_max = fvec3_to_vec3(player.spawn.speed_max);
	/*
	res.physic.look = fvec2_to_vec2(player.physic.look);
	if (res.physic.look.v < M_PI / 2 && res.physic.look.v > -M_PI / 2)
		res.physic.look.v = 0;
		*/
	return (res);
}

t_vec2		*parse_points(void *buf, size_t npoints, size_t index, size_t max)
{
	t_c_point	struc_p;
	t_vec2		*n_point;
	size_t		i;

	n_point = (t_vec2 *)malloc(sizeof(t_vec2) * npoints);
	i = 0;
	while (i < npoints)
	{
		struc_p = *(t_c_point *)dump_struct(buf, index + sizeof(t_c_point) * i, sizeof(t_c_point), max);
		verify_magic(&struc_p, POINT_MAGIC, i);
		n_point[i] = fvec2_to_vec2(struc_p.point);
		i++;
	}
	return (n_point);
}

t_wall		*parse_walls(void *buf, size_t nwalls, size_t index, size_t max)
{
	t_c_wall	struc_w;
	t_wall		*n_walls;
	size_t		i;

	n_walls = (t_wall *)malloc(sizeof(t_wall) * nwalls);
	i = 0;
	while (i < nwalls)
	{
		struc_w = *(t_c_wall *)dump_struct(buf, index + sizeof(t_c_wall) * i, sizeof(t_c_wall), max);
		verify_magic(&struc_w, WALL_MAGIC, i);
		n_walls[i].portal = struc_w.portal;
		n_walls[i].a = struc_w.a;
		n_walls[i].b = struc_w.b;
		n_walls[i].mat = NULL;
		i++;
	}
	return (n_walls);
}

t_sector	*parse_sectors(void *buf, size_t nsectors, size_t index, size_t max)
{
	t_c_sector	struc_s;
	t_sector	*n_sectors;
	size_t		i;

	n_sectors = (t_sector *)malloc(sizeof(t_sector) * nsectors);
	i = 0;
	while (i < nsectors)
	{
		struc_s = *(t_c_sector *)dump_struct(buf, index + sizeof(t_c_sector) * i, sizeof(t_c_sector), max);
		verify_magic(&struc_s, SECTOR_MAGIC, i);
		n_sectors[i].start = struc_s.start;
		n_sectors[i].number = struc_s.number;
		n_sectors[i].sector_id = struc_s.sector_id;
		n_sectors[i].floor = f_to_float(struc_s.floor);
		n_sectors[i].ceiling = f_to_float(struc_s.ceiling);
		n_sectors[i].ambient = struc_s.ambient;
		n_sectors[i].ceiling_mat = NULL;
		n_sectors[i].floor_mat = NULL;
		i++;
	}
	return (n_sectors);
}

t_portal	*parse_portals(void *buf, size_t nportals, size_t index, size_t max)
{
	t_c_portal	struc_p;
	t_portal	*n_portals;
	size_t		i;

	n_portals = (t_portal *)malloc(sizeof(t_portal) * nportals);
	i = 0;
	while (i < nportals)
	{
		struc_p = *(t_c_portal *)dump_struct(buf, index + sizeof(t_c_portal) * i, sizeof(t_c_portal), max);
		verify_magic(&struc_p, PORTAL_MAGIC, i);
		n_portals[i].from_sector = struc_p.from_sector;
		n_portals[i].to_sector = struc_p.to_sector;
		n_portals[i].from_wall = struc_p.from_wall;
		n_portals[i].to_wall = struc_p.to_wall;
		n_portals[i].a = struc_p.a;
		n_portals[i].b = struc_p.b;
		i++;
	}
	return (n_portals);
}

t_game		load(const char *filename)
{
	void		*buf;
	size_t		max;
	t_c_game	game;
	t_game		res;

	buf = dump_file(filename, 0, &max);
	game = *(t_c_game *)dump_struct(buf, 0, sizeof(t_c_game), max);
	verify_magic(&game, GAME_MAGIC, 0);
	res.player = parse_player(game.player);
	res.points = parse_points(buf, game.npoints, LOC_POINT, max);
	res.npoints	= game.npoints;
	res.walls = parse_walls(buf, game.nwalls, LOC_WALL(game.npoints), max);
	res.nwalls = game.nwalls;
	res.sectors = parse_sectors(buf, game.nsectors, LOC_SECTOR(game.npoints, game.nwalls), max);
	res.nsectors = game.nsectors;
	res.portals = parse_portals(buf, game.nportals, LOC_PORTAL(game.npoints, game.nwalls, game.nsectors), max);
	res.nportals = game.nportals;
	// debug(res);
	return (res);
}
