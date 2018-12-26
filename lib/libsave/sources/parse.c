/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 13:46:22 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/26 12:51:01 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structure_clone.h>
#include <../../../includes/doom.h>

static void	*dump_struct(void *buf, size_t start, size_t size, size_t max)
{
	if (start + size < max)
		return (buf + start);
	else
		exit_error("FileLoader3030: File corrupted"\
		C_RESET\
		" (error no. 0xbalkaNES)");
	return (NULL);
}

static void	verify_magic(void *t_c_struct, size_t magic, size_t index)
{
	if (*(size_t *)t_c_struct != magic + index)
		exit_error("FileLoader3030: File corrupted"\
		C_RESET\
		" (error no. 0xbalkaMNI)");
}

void		debug(t_game game)
{
	printf("player.ph.gravity: %f\n", game.player.ph_enabled.gravity);
	printf("player.ph.height: %f\n", game.player.ph_enabled.height);
	printf("player.ph.pos: {%f, %f, %f}\n", game.player.ph_enabled.pos.x, game.player.ph_enabled.pos.y, game.player.ph_enabled.pos.z);
	printf("player.ph.speed: {%f, %f, %f}\n", game.player.ph_enabled.pos.x, game.player.ph_enabled.pos.y, game.player.ph_enabled.pos.z);
	printf("player.ph.speed_max: {%f, %f, %f}\n", game.player.ph_enabled.speed_max.x, game.player.ph_enabled.speed_max.y, game.player.ph_enabled.speed_max.z);
	printf("player.ph.look: {%f, %f}\n", game.player.ph_enabled.look.u, game.player.ph_enabled.look.v);
}

t_player	parse_player(t_c_player player)
{
	t_player	res;

	res = player_default();
	res.ph_enabled.gravity = f_to_float(player.physic.gravity);
	res.ph_enabled.height = f_to_float(player.physic.height);
	res.ph_enabled.pos = fvec3_to_vec3(player.physic.pos);
	res.ph_enabled.speed_max = fvec3_to_vec3(player.physic.speed_max);
	res.ph_enabled.look = fvec2_to_vec2(player.physic.look);
	if (res.ph_enabled.look.v < M_PI / 2 && res.ph_enabled.look.v > -M_PI / 2)
		res.ph_enabled.look.v = 0;
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
