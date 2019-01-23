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

	res.physic.gravity = f_from_float(player.physic.gravity);
	res.physic.height = f_from_float(player.physic.height);
	res.physic.pos = vec3_to_fvec3(player.physic.pos);
	res.physic.speed_max = vec3_to_fvec3(player.physic.pos);
	//res.physic.look = vec2_to_fvec2(player.physic.look);
	return (res);
}

void		save(const char *filename, t_game game)
{
	t_c_game	to_save;
	int			fd;

	to_save.magic = GAME_MAGIC;
	to_save.player = translate_player(game.player);
	to_save.sectors = 0;
	to_save.nsectors = 0;
	to_save.walls = 0;
	to_save.nwalls = 0;
	to_save.portals = 0;
	to_save.nportals = 0;
	to_save.points = 0;
	to_save.npoints = 0;
	fd = open_file(filename, 1, NULL);
	if ((write(fd, &to_save, sizeof(t_c_game))) >= 0)
		console_log("FileLoader3030", "Successfully saved file.");
	else
	{
		close(fd);
		console_error("FileLoader3030", "File saving failed.");
		perror_quit();
	}
	close(fd);
}
