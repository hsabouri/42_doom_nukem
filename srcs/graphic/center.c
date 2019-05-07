/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:46:59 by fmerding          #+#    #+#             */
/*   Updated: 2019/05/07 13:06:32 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	find_center_sectors(t_game game)
{
	size_t n;
	unsigned int i;

	n = 0;
	i = 0;
	while (n < 1)
	{
		// reverse_walls(game, n);
		find_center(game, n);
		// reverse_walls(games,n);
		sort_tab_z(n, i, game);
		rotate_floor(n, 0, game);
		rotate_ceiling(n, 0, game);
		n++;
	}
}
//

void reverse_walls(t_game game, size_t n)
{
	unsigned int i;
	unsigned int j;
	unsigned int tmp;

	i = game.sectors[n].start;
	j = game.sectors[n].start+1;
	while ( i < game.sectors[n].number + game.sectors[n].start)
	{
		if (game.sectors[n].clock == 0)
		{
			if (game.walls[i].a != game.walls[j].a && j < game.sectors[n].number + game.sectors[n].start)
				j++;
			if (game.walls[i].a == game.walls[j].a)
			{
				tmp = game.walls[j].a;
				game.walls[j].a = game.walls[j].b;
				game.walls[j].b = tmp;
			}
			i++;
		}
		if (game.sectors[n].clock == 1)
		{
			if (game.walls[i].b != game.walls[j].b && j < game.sectors[n].number + game.sectors[n].start)
				j++;
			if (game.walls[i].b == game.walls[j].b)
			{
				tmp = game.walls[j].a;
				game.walls[j].b = game.walls[j].a;
				game.walls[j].a = tmp;
			}
			i++;
		}
	}
}

void	find_center(t_game game, size_t n)
{
	t_vec2 res;
	unsigned int i;
	int j;
	int tab[game.sectors[n].number];

	res.u = 0;
	res.v = 0;
	i = 0;
	j = game.sectors[n].start;
	while (i < game.sectors[n].number)
	{
		tab[i] = game.walls[j].a;
		i++;
		j++;
	}
	i = 0;
	while( i < game.sectors[n].number)
	{
		res.u += game.points[tab[i]].u;
		res.v += game.points[tab[i]].v;
		i++;
	}
	res.u /= i;
	res.v /= i;
	game.sectors[n].center.u = res.u;
	game.sectors[n].center.v = res.v;

	// printf(" center %zu x = %f y = %f\n",n,game.sectors[n].center.u, game.sectors[n].center.v);
}

// void	apply_z(size_t n, unsigned int i, t_game game)
// {
// 	int i =
// 	while (i < game.sectors[n].number)
// 	{
// 		newx = game.points[game.walls[game.sectors[n].sort_v[i]].a].u - game.sectors[n].center.u;
// 		newy = game.points[game.walls[game.sectors[n].sort_v[i]].a].v - game.sectors[n].center.v;
// 		game.walls[game.sectors[n].sort_v[i]].left_z.v = newx * game.sectors[n].floor.x + newy * game.sectors[n].floor.y + game.sectors[n].floor.z;
// 	}
// }


void	sort_tab_z(size_t n, unsigned int i, t_game game)
{
	int *tab;
	unsigned int j;

	i = 0;
	j = 0;
	j = game.sectors[n].start;
	tab = malloc(sizeof (int) * game.sectors[n].number);
	game.sectors[n].sort_v = malloc(sizeof (int) * game.sectors[n].number);
	while (i < game.sectors[n].number)
	{

		game.sectors[n].sort_v[i] = j;
		printf("game.walls[%d].a = %d\n",j,game.walls[j].a);
		i++;
		j++;
	}

}
