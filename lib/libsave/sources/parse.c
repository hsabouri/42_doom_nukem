/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 13:46:22 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/27 18:26:53 by hugo             ###   ########.fr       */
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
	printf("player.ph.gravity: %f\n", game.player.physic.gravity);
	printf("player.ph.height: %f\n", game.player.physic.height);
	printf("player.ph.pos: {%f, %f, %f}\n", game.player.physic.pos.x, game.player.physic.pos.y, game.player.physic.pos.z);
	printf("player.ph.speed: {%f, %f, %f}\n", game.player.physic.pos.x, game.player.physic.pos.y, game.player.physic.pos.z);
	printf("player.ph.speed_max: {%f, %f, %f}\n", game.player.physic.speed_max.x, game.player.physic.speed_max.y, game.player.physic.speed_max.z);
	printf("player.ph.look: {%f, %f}\n", game.player.physic.look.u, game.player.physic.look.v);
}

t_player	parse_player(t_c_player player)
{
	t_player	res;

	res = player_default();
	res.physic.gravity = f_to_float(player.physic.gravity);
	res.physic.height = f_to_float(player.physic.height);
	res.physic.pos = fvec3_to_vec3(player.physic.pos);
	res.physic.speed_max = fvec3_to_vec3(player.physic.speed_max);
	res.physic.look = fvec2_to_vec2(player.physic.look);
	if (res.physic.look.v < M_PI / 2 && res.physic.look.v > -M_PI / 2)
		res.physic.look.v = 0;
	return (res);
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
	debug(res);
	return (res);
}
