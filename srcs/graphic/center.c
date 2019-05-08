/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:46:59 by fmerding          #+#    #+#             */
/*   Updated: 2019/05/08 15:56:54 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			find_center_sectors(t_game game)
{
	size_t			n;
	unsigned int	i;

	n = 0;
	i = 0;
	while (n < game.nsectors)
	{
		find_center(game, n);
		n++;
	}
}

void			find_center(t_game game, size_t n)
{
	t_vec2			res;
	unsigned int	i;
	int				j;
	int				tab[game.sectors[n].number];

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
	while (i < game.sectors[n].number)
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

t_cache_wall		switch_points(t_cache_wall current, t_game game, size_t i)
{
	t_vec3 a;
	t_vec3 b;

	b.x = (game.points[game.walls[i].a].u + game.points[game.walls[i].b].u)
	/ 2 - game.player.my_entity.physic.pos.x;
	b.y = (game.points[game.walls[i].a].v + game.points[game.walls[i].b].v)
	/ 2 - game.player.my_entity.physic.pos.y;
	a.x = game.points[game.walls[i].a].u - game.player.my_entity.physic.pos.x;
	a.y = game.points[game.walls[i].a].v - game.player.my_entity.physic.pos.y;
	if (((b.x * a.y) - (a.x * b.y)) < 0)
	{
		current.left_z = game.points[game.walls[i].b];
		current.right_z = game.points[game.walls[i].a];
	}
	return (current);
}
