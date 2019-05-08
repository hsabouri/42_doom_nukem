/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 13:14:28 by fmerding          #+#    #+#             */
/*   Updated: 2019/05/08 15:58:30 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float	find_z(t_context context, t_vec2 point, int mode)
{
	float newx;
	float newy;
	float z;

	if (mode == 1)
	{
		newx = point.u - context.sector.center.u;
		newy = point.v - context.sector.center.v;
		z = newx * context.sector.floor.x + newy * context.sector.floor.y
		+ context.sector.floor.z;
	}
	if (mode == 0)
	{
		newx = point.u - context.sector.center.u;
		newy = point.v - context.sector.center.v;
		z = newx * context.sector.ceiling.x + newy * context.sector.ceiling.y
		+ context.sector.ceiling.z;
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

void	rotate_floor(size_t n, int mode, t_game game)
{
	if (mode == 1)
	{
		game.sectors[n].floor.y += 0.1;
		if (check_z_limits(n, game) == 0)
			game.sectors[n].floor.y -= 0.1;
	}
	if (mode == 2)
	{
		game.sectors[n].floor.y -= 0.1;
		if (check_z_limits(n, game) == 0)
			game.sectors[n].floor.y += 0.1;
	}
	if (mode == 3)
	{
		game.sectors[n].floor.x += 0.1;
		if (check_z_limits(n, game) == 0)
			game.sectors[n].floor.x -= 0.1;
	}
	if (mode == 4)
	{
		game.sectors[n].floor.x -= 0.1;
		if (check_z_limits(n, game) == 0)
			game.sectors[n].floor.x += 0.1;
	}
}

void	rotate_ceiling(size_t n, int mode, t_game game)
{
	if (mode == 1)
	{
		game.sectors[n].ceiling.y += 0.1;
		if (check_z_limits(n, game) == 0)
			game.sectors[n].ceiling.y -= 0.1;
	}
	if (mode == 2)
	{
		game.sectors[n].ceiling.y -= 0.1;
		if (check_z_limits(n, game) == 0)
			game.sectors[n].ceiling.y += 0.1;
	}
	if (mode == 3)
	{
		game.sectors[n].ceiling.x += 0.1;
		if (check_z_limits(n, game) == 0)
			game.sectors[n].ceiling.x -= 0.1;
	}
	if (mode == 4)
	{
		game.sectors[n].ceiling.x -= 0.1;
		if (check_z_limits(n, game) == 0)
			game.sectors[n].ceiling.x += 0.1;
	}
}
