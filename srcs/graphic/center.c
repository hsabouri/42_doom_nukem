/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:46:59 by fmerding          #+#    #+#             */
/*   Updated: 2019/05/07 18:25:35 by fmerding         ###   ########.fr       */
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
		find_center(game, n);
		// sort_tab_z(n, i, game);
		// rotate_floor(n, 0, game);
		// rotate_ceiling(n, 0, game);
		n++;
	}
}
//
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

}
