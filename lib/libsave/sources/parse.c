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

	printf("player.physic.gravity: %f\n", game.player.physic.gravity);
	printf("player.physic.height: %f\n", game.player.physic.height);
	printf("player.physic.pos: {%f, %f, %f}\n", game.player.physic.pos.x, game.player.physic.pos.y, game.player.physic.pos.z);
	printf("player.physic.speed: {%f, %f, %f}\n", game.player.physic.pos.x, game.player.physic.pos.y, game.player.physic.pos.z);
	printf("player.physic.speed_max: {%f, %f, %f}\n", game.player.physic.speed_max.x, game.player.physic.speed_max.y, game.player.physic.speed_max.z);
	// printf("player.physic.look: {%f, %f}\n", game.player.physic.look.u, game.player.physic.look.v);

	i = 0;
	while (i < (int)game.npoints)
	{
		printf("player.points.u: %f, player.points.v: %f\n", game.points[i].u, game.points[i].v);
		i++;
	}
	printf("player.npoints: %zu\n", game.npoints);
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
	res.points = parse_points(buf, game.npoints, sizeof(t_c_game), max);
	res.npoints	= game.npoints;
	debug(res);
	return (res);
}
