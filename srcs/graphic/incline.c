/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 13:14:28 by fmerding          #+#    #+#             */
/*   Updated: 2019/05/07 12:25:12 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <doom.h>


unsigned int find_right(t_game game, int* tab, size_t n, int i)
{
	unsigned int res;
	unsigned int left;
	// left = find_left(game, tab, n, i);
	res = game.walls[tab[i]].b;
	left = game.sectors[n].start;
	while (game.walls[left].a != res)
		left++;
	return(left);
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
	while (i < game.sectors[n].number)
	{
		newx = game.points[game.walls[game.sectors[n].sort_v[i]].a].u - game.sectors[n].center.u;
		newy = game.points[game.walls[game.sectors[n].sort_v[i]].a].v - game.sectors[n].center.v;
		game.walls[game.sectors[n].sort_v[i]].left_z.v = newx * game.sectors[n].floor.x + newy * game.sectors[n].floor.y + game.sectors[n].floor.z;
		// if ((n % 2 == 0 && game.walls[game.sectors[n].sort_v[i]].left_z.v > game.walls[game.sectors[n].sort_v[i]].left_z.u) || (n % 2 == 1 && game.walls[game.sectors[n].sort_v[i]].right_z.v > game.walls[game.sectors[n].sort_v[i]].right_z.u))
		// rip = 1;
		printf("a = %d , b = %d\n",game.walls[game.sectors[n].sort_v[i]].a,
		game.walls[game.sectors[n].sort_v[i]].b);
		i++;

	}
	i = 0;

	while (i < game.sectors[n].number)
	{
		newx = game.points[game.walls[game.sectors[n].sort_v[i]].b].u - game.sectors[n].center.u;
		newy = game.points[game.walls[game.sectors[n].sort_v[i]].b].v - game.sectors[n].center.v;
		game.walls[game.sectors[n].sort_v[i]].right_z.v = newx * game.sectors[n].floor.x + newy * game.sectors[n].floor.y + game.sectors[n].floor.z;
		// printf("left_z = %f, right_z = %f\n",game.walls[game.sectors[n].sort_v[i]].left_z.v,game.walls[game.sectors[n].sort_v[i]].right_z.v);
		i++;
	}
	i = 0;
	if (game.sectors[n].clock == 0)
	{
		while (i < game.sectors[n].number)
		{
			tmp = game.walls[game.sectors[n].sort_v[i]].right_z.v;
			game.walls[game.sectors[n].sort_v[i]].right_z.v = game.walls[game.sectors[n].sort_v[i]].left_z.v;
			game.walls[game.sectors[n].sort_v[i]].left_z.v = tmp;
			i++;
		}
	}
	if (rip == 1)
	{
		if (mode == 1)
			rotate_floor(n, 2 , game);
		if (mode == 2)
			rotate_floor(n, 1 , game);
		if (mode == 3)
			rotate_floor(n, 4 , game);
		if (mode == 4)
			rotate_floor(n, 3 , game);
	}
	// printf()
	printf("\n\n");
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

	while (i < game.sectors[n].number)
	{
		newx = game.points[game.walls[game.sectors[n].sort_v[i]].a].u - game.sectors[n].center.u;
		newy = game.points[game.walls[game.sectors[n].sort_v[i]].a].v - game.sectors[n].center.v;
		// if (n % 2 == 0)
		// {
		game.walls[game.sectors[n].sort_v[i]].left_z.u = newx * game.sectors[n].ceiling.x + newy * game.sectors[n].ceiling.y + game.sectors[n].ceiling.z;
		// if ((n % 2 == 0 && game.walls[game.sectors[n].sort_v[i]].left_z.v > game.walls[game.sectors[n].sort_v[i]].left_z.u) || (n % 2 == 1 && game.walls[game.sectors[n].sort_v[i]].right_z.v > game.walls[game.sectors[n].sort_v[i]].right_z.u))
		// rip = 1;
		i++;
	}
	i = 0;

	while (i < game.sectors[n].number)
	{
		newx = game.points[game.walls[game.sectors[n].sort_v[i]].b].u - game.sectors[n].center.u;
		newy = game.points[game.walls[game.sectors[n].sort_v[i]].b].v - game.sectors[n].center.v;
		game.walls[game.sectors[n].sort_v[i]].right_z.u = newx * game.sectors[n].ceiling.x + newy * game.sectors[n].ceiling.y + game.sectors[n].ceiling.z;

		// printf("left_z = %f, right_z = %f\n",game.walls[game.sectors[n].sort_v[i]].left_z.u,game.walls[game.sectors[n].sort_v[i]].right_z.u);
		i++;
	}
	i = 0;
	if (game.sectors[n].clock == 0)
	{
		while (i < game.sectors[n].number)
		{
			tmp = game.walls[game.sectors[n].sort_v[i]].right_z.u;
			game.walls[game.sectors[n].sort_v[i]].right_z.u = game.walls[game.sectors[n].sort_v[i]].left_z.u;
			game.walls[game.sectors[n].sort_v[i]].left_z.u = tmp;
			i++;
		}
	}
	if (rip == 1)
	{
		if (mode == 1)
			rotate_ceiling(n, 2 , game);
		if (mode == 2)
			rotate_ceiling(n, 1 , game);
		if (mode == 3)
			rotate_ceiling(n, 4 , game);
		if (mode == 4)
			rotate_ceiling(n, 3 , game);
	}



}
