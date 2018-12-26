/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 11:36:35 by hugo              #+#    #+#             */
/*   Updated: 2018/12/26 13:06:15 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structure_clone.h>
#include <../../../includes/doom.h>

t_c_player	translate_player(t_player player)
{
	t_c_player	res;

	res.physic.gravity = f_from_float(player.ph_enabled.gravity);
	res.physic.height = f_from_float(player.ph_enabled.height);
	res.physic.pos = vec3_to_fvec3(player.ph_enabled.pos);
	res.physic.speed_max = vec3_to_fvec3(player.ph_enabled.pos);
	res.physic.look = vec2_to_fvec2(player.ph_enabled.look);
	return (res);
}

void		save(t_game game, int fd)
{
	t_c_game	to_save;

	to_save.magic = GAME_MAGIC;
	to_save.player = save_player(game.player);
	to_save.sectors = 0;
	to_save.nsectors = 0;
	to_save.walls = 0;
	to_save.nwalls = 0;
	to_save.portals = 0;
	to_save.nportals = 0;
	to_save.points = 0;
	to_save.npoints = 0;
	write(fd, &to_save, sizeof(t_c_game));
}