/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:46:59 by fmerding          #+#    #+#             */
/*   Updated: 2019/04/29 17:01:00 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	find_center_sectors(t_game game)
{
	size_t n;
	unsigned int i;

	n = 0;
	i = 0;
	while (n < game.nsectors )
	{
		find_center(game, n);
		sort_tab_z(n, i, game);
		n++;
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
		game.walls[j].left_z.u = game.sectors[n].ceiling.z;
		game.walls[j].right_z.u = game.sectors[n].ceiling.z;
		game.walls[j].left_z.v = game.sectors[n].floor.z;
		game.walls[j].right_z.v = game.sectors[n].floor.z;
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
}

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
		game.sectors[n].sort_v[i] = game.walls[j].a;
		i++;
		j++;
	}
}
