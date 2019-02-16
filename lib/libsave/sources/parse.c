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
	while (i < (int)game.nmaterials)
	{
		printf("materials.pos.u: %f, materials.pos.v: %f, materials.sca.u: %f, materials.sca.v: %f\n", \
		f_to_float(game.materials[i].pos.u), f_to_float(game.materials[i].pos.v), f_to_float(game.materials[i].sca.u), f_to_float(game.materials[i].sca.v));
		i++;
	}
	printf("nmats: %zu\n", game.nmaterials);
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

t_mat		*parse_mats(void *buf, size_t nmats, size_t index, size_t max)
{
	t_c_mat	struc_m;
	t_mat	*materials;
	size_t	i;

	materials = (t_mat *)malloc(sizeof(t_mat) * nmats);
	i = 0;
	while (i < nmats)
	{
		struc_m = *(t_c_mat *)dump_struct(buf, index + sizeof(t_c_mat) * i, sizeof(t_c_mat), max);
		verify_magic(&struc_m, MAT_MAGIC, i);
		materials[i].pos.u = struc_m.pos.u;
		materials[i].pos.v = struc_m.pos.v;
		materials[i].sca.u = struc_m.sca.u;
		materials[i].sca.v = struc_m.sca.v;
		materials[i].color = struc_m.color;
		materials[i].texture = struc_m.texture;
		materials[i].mode = struc_m.mode;
		materials[i].filter = struc_m.filter;
		if (struc_m.overlay != -1)
			materials[i].overlay = id_to_p(struc_m.overlay, materials, sizeof(t_mat));
		else
			materials[i].overlay = NULL;
		i++;
	}
	return (materials);
}

t_vec2		*parse_points(void *buf, size_t npoints, size_t index, size_t max)
{
	t_c_point	struc_p;
	t_vec2		*points;
	size_t		i;

	points = (t_vec2 *)malloc(sizeof(t_vec2) * npoints);
	i = 0;
	while (i < npoints)
	{
		struc_p = *(t_c_point *)dump_struct(buf, index + sizeof(t_c_point) * i, sizeof(t_c_point), max);
		verify_magic(&struc_p, POINT_MAGIC, i);
		points[i] = fvec2_to_vec2(struc_p.point);
		i++;
	}
	return (points);
}

t_wall		*parse_walls(void *buf, size_t nwalls, size_t index, size_t max, t_mat *mats)
{
	t_c_wall	struc_w;
	t_wall		*walls;
	size_t		i;

	walls = (t_wall *)malloc(sizeof(t_wall) * nwalls);
	i = 0;
	while (i < nwalls)
	{
		struc_w = *(t_c_wall *)dump_struct(buf, index + sizeof(t_c_wall) * i, sizeof(t_c_wall), max);
		verify_magic(&struc_w, WALL_MAGIC, i);
		walls[i].portal = struc_w.portal;
		walls[i].a = struc_w.a;
		walls[i].b = struc_w.b;
		walls[i].mat = id_to_p((ssize_t)struc_w.mat, mats, sizeof(t_mat));
		i++;
	}
	return (walls);
}

t_sector	*parse_sectors(void *buf, size_t nsectors, size_t index, size_t max, t_mat	*mats)
{
	t_c_sector	struc_s;
	t_sector	*sectors;
	size_t		i;

	sectors = (t_sector *)malloc(sizeof(t_sector) * nsectors);
	i = 0;
	while (i < nsectors)
	{
		struc_s = *(t_c_sector *)dump_struct(buf, index + sizeof(t_c_sector) * i, sizeof(t_c_sector), max);
		verify_magic(&struc_s, SECTOR_MAGIC, i);
		sectors[i].start = struc_s.start;
		sectors[i].number = struc_s.number;
		sectors[i].sector_id = struc_s.sector_id;
		sectors[i].floor = f_to_float(struc_s.floor);
		sectors[i].ceiling = f_to_float(struc_s.ceiling);
		sectors[i].ambient = struc_s.ambient;
		sectors[i].ceiling_mat = id_to_p((ssize_t)struc_s.ceiling_mat, mats, sizeof(t_mat));
		sectors[i].floor_mat = id_to_p((ssize_t)struc_s.floor_mat, mats, sizeof(t_mat));
		i++;
	}
	return (sectors);
}

t_portal	*parse_portals(void *buf, size_t nportals, size_t index, size_t max)
{
	t_c_portal	struc_p;
	t_portal	*portals;
	size_t		i;

	portals = (t_portal *)malloc(sizeof(t_portal) * nportals);
	i = 0;
	while (i < nportals)
	{
		struc_p = *(t_c_portal *)dump_struct(buf, index + sizeof(t_c_portal) * i, sizeof(t_c_portal), max);
		verify_magic(&struc_p, PORTAL_MAGIC, i);
		portals[i].from_sector = struc_p.from_sector;
		portals[i].to_sector = struc_p.to_sector;
		portals[i].from_wall = struc_p.from_wall;
		portals[i].to_wall = struc_p.to_wall;
		portals[i].a = struc_p.a;
		portals[i].b = struc_p.b;
		i++;
	}
	return (portals);
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
	res.materials = parse_mats(buf, game.nmaterials, LOC_MAT, max);
	res.nmaterials = game.nmaterials;
	res.points = parse_points(buf, game.npoints, LOC_POINT(game.nmaterials), max);
	res.npoints	= game.npoints;
	res.walls = parse_walls(buf, game.nwalls, LOC_WALL(game.nmaterials, game.npoints), max, res.materials);
	res.nwalls = game.nwalls;
	res.sectors = parse_sectors(buf, game.nsectors, LOC_SECTOR(game.nmaterials, game.npoints, game.nwalls), max, res.materials);
	res.nsectors = game.nsectors;
	res.portals = parse_portals(buf, game.nportals, LOC_PORTAL(game.nmaterials, game.npoints, game.nwalls, game.nsectors), max);
	res.nportals = game.nportals;
	// debug(res);
	return (res);
}
