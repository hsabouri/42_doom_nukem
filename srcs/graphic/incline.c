/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 13:14:28 by fmerding          #+#    #+#             */
/*   Updated: 2019/04/29 17:01:22 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void rotate_floor(size_t n, int mode, t_game game)
{
	t_vec2 new;
	int *tab;
	int i = game.sectors[n].number - 1;
	int right;
	int rip;

	rip = 0;
	if (mode == 1)
		game.sectors[n].floor.y += 0.1;
	if (mode == 2)
		game.sectors[n].floor.y -= 0.1;
	if (mode == 3)
		game.sectors[n].floor.x += 0.1;
	if (mode == 4)
		game.sectors[n].floor.x -= 0.1;
	tab = game.sectors[n].sort_v;
	while (i >= 0)
	{
		new.u = game.points[tab[i]].v - game.sectors[n].center.v;
		new.v = game.points[tab[i]].u - game.sectors[n].center.u;
		game.walls[tab[i]].left_z.v = new.u *game.sectors[n].floor.x + new.v *game.sectors[n].floor.y +
		game.sectors[n].floor.z ;
		if (game.walls[tab[i]].left_z.v > game.walls[tab[i]].left_z.u)
			rip = 1;
		i--;
	}
	i = game.sectors[n].number - 1;
	while (i >= 0)
	{
		right = find_right(game, tab, n, i);
		game.walls[tab[i]].right_z.v = game.walls[right].left_z.v;
		i--;
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
}

void rotate_ceiling(size_t n, int mode, t_game game)
{
	t_vec2 new;
	int *tab;
	int i = game.sectors[n].number - 1;
	int right;
	int rip;

	rip = 0;
	if (mode == 1)
		game.sectors[n].ceiling.y += 0.1;
	if (mode == 2)
		game.sectors[n].ceiling.y -= 0.1;
	if (mode == 3)
		game.sectors[n].ceiling.x += 0.1;
	if (mode == 4)
		game.sectors[n].ceiling.x -= 0.1;
	tab = game.sectors[n].sort_v;
	while (i >= 0)
	{
		new.u = game.points[tab[i]].v - game.sectors[n].center.v;
		new.v = game.points[tab[i]].u - game.sectors[n].center.u;
		game.walls[tab[i]].left_z.u = new.u *game.sectors[n].ceiling.x + new.v *game.sectors[n].ceiling.y +
		game.sectors[n].ceiling.z ;
		if (game.walls[tab[i]].left_z.v > game.walls[tab[i]].left_z.u)
			rip = 1;
		i--;
	}
	i = game.sectors[n].number - 1;
	while (i >= 0)
	{
		right = find_right(game, tab, n, i);
		game.walls[tab[i]].right_z.u = game.walls[right].left_z.u;
		i--;
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

unsigned int find_right(t_game game, int* tab, size_t n, int i)
{
	unsigned int res;

	res = game.walls[tab[i]].a;
	i = game.sectors[n].number - 1;
	while (game.walls[tab[i]].b != res)
		i--;
	return(tab[i]);
}
