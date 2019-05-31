/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:46:59 by fmerding          #+#    #+#             */
/*   Updated: 2019/05/30 17:15:15 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		find_center_sectors(t_game game)
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

void		find_center(t_game game, size_t n)
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
	game.sectors[n].center.u = res.u / i;
	game.sectors[n].center.v = res.v / i;
}

size_t		find_sector_portals(t_game game, size_t wall)
{
	size_t	res;
	size_t	i;

	res = 0;
	i = 0;
	while (game.portals[i].from_wall != wall && game.portals[i].to_wall
		!= wall)
		i++;
	if (game.portals[i].from_wall == wall)
		res = game.portals[i].from_sector;
	if (game.portals[i].to_wall == wall)
		res = game.portals[i].to_sector;
	return (res);
}

size_t		find_wall_portal(t_game game, size_t wall)
{
	size_t i;

	i = 0;
	while (game.portals[i].from_wall != wall && game.portals[i].to_wall != wall)
		i++;
	if (game.portals[i].from_wall == wall)
		return (game.portals[i].to_wall);
	return (game.portals[i].from_wall);
}

size_t		find_wall_order(t_game game, size_t wall)
{
	size_t i;

	i = 0;
	while ((game.portals[i].from_wall != wall && game.portals[i].to_wall
		!= wall) && i < game.nportals)
		i++;
	if (game.portals[i].from_wall == wall)
		return (0);
	if (game.portals[i].to_wall == wall)
		return (1);
	return (2);
}
