/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 13:14:28 by fmerding          #+#    #+#             */
/*   Updated: 2019/05/07 18:26:51 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <doom.h>


unsigned int find_right(t_game game, int* tab, size_t n, int i)
{
	unsigned int res;
	unsigned int left;
	res = game.walls[tab[i]].b;
	left = game.sectors[n].start;
	while (game.walls[left].a != res)
		left++;
	return(left);
}

float find_z(t_context game, t_vec2 point, int mode)
{
	float newx;
	float newy;
	float z;

	if (mode == 1)
	{
		newx = point.u - game.sector.center.u;
		newy = point.v - game.sector.center.v;
		z = newx * game.sector.floor.x + newy * game.sector.floor.y + game.sector.floor.z;
	}

	if (mode == 0)
	{
		newx = point.u - game.sector.center.u;
		newy = point.v - game.sector.center.v;
		z = newx * game.sector.ceiling.x + newy * game.sector.ceiling.y + game.sector.ceiling.z;
	}
	return (z);
}

void rotate_floor(size_t n, int mode, t_game game)
{
	int rip;
	unsigned int i;
	float newx;
	float newy;
	float tmp;
	newx = 0;
	newy = 0;
	rip = 0;
	i = 0;

	if (mode == 1)
		game.sectors[n].floor.y += 0.1;
	if (mode == 2)
		game.sectors[n].floor.y -= 0.1;
	if (mode == 3)
		game.sectors[n].floor.x += 0.1;
	if (mode == 4)
		game.sectors[n].floor.x -= 0.1;
}

void rotate_ceiling(size_t n, int mode, t_game game)
{
	int rip;
	unsigned int i;
	float newx;
	float newy;
	float tmp;

	newx = 0;
	newy = 0;
	rip = 0;
	i = 0;
	if (mode == 1)
		game.sectors[n].ceiling.y += 0.1;
	if (mode == 2)
		game.sectors[n].ceiling.y -= 0.1;
	if (mode == 3)
		game.sectors[n].ceiling.x += 0.1;
	if (mode == 4)
		game.sectors[n].ceiling.x -= 0.1;
}
