/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 13:14:28 by fmerding          #+#    #+#             */
/*   Updated: 2019/05/31 14:24:41 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_fixed	find_z(t_sector sector, t_vec2 point, int mode)
{
	t_fixed newx;
	t_fixed newy;
	t_fixed z;

	if (mode == 1)
	{
		newx = f_from_float(point.u - sector.center.u);
		newy = f_from_float(point.v - sector.center.v);
		z = f_mul(newx, f_from_float(sector.floor.x)) + f_mul(newy,
			f_from_float(sector.floor.y)) + f_from_float(sector.floor.z);
	}
	if (mode == 0)
	{
		newx = f_from_float(point.u - sector.center.u);
		newy = f_from_float(point.v - sector.center.v);
		z = f_mul(newx, f_from_float(sector.ceiling.x)) + f_mul(newy,
			f_from_float(sector.ceiling.y)) + f_from_float(sector.ceiling.z);
	}
	return (z);
}

int		check_z_game(size_t n, int i, t_game game)
{
	float newx;
	float newy;
	float z1;
	float z2;

	i += game.sectors[n].start;
	newx = game.points[game.walls[i].a].u - game.sectors[n].center.u;
	newy = game.points[game.walls[i].a].v - game.sectors[n].center.v;
	z1 = newx * game.sectors[n].floor.x + newy * game.sectors[n].floor.y
	+ game.sectors[n].floor.z;
	z2 = newx * game.sectors[n].ceiling.x + newy * game.sectors[n].ceiling.y
	+ game.sectors[n].ceiling.z;
	if (z2 < z1)
		return (0);
	return (1);
}

int		check_z_limits(size_t n, t_game game)
{
	unsigned int	i;
	int				res;

	i = 0;
	res = 1;
	while (i < game.sectors[n].number)
	{
		res = check_z_game(n, i, game);
		if (res == 0)
			return (0);
		i++;
	}
	return (1);
}
