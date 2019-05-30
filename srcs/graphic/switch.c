/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:02:11 by fmerding          #+#    #+#             */
/*   Updated: 2019/05/30 17:20:26 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_cache_wall	switch_points(t_cache_wall current, t_game game, size_t i,
	t_context context)
{
	t_fvec3	a;
	t_fvec3	b;

	b.x = f_from_float((game.points[game.walls[i].a].u
		+ game.points[game.walls[i].b].u) / 2 - context.physic.pos.x);
	b.y = f_from_float((game.points[game.walls[i].a].v
		+ game.points[game.walls[i].b].v) / 2 - context.physic.pos.y);
	a.x = f_from_float(game.points[game.walls[i].a].u - context.physic.pos.x);
	a.y = f_from_float(game.points[game.walls[i].a].v - context.physic.pos.y);
	if ((f_mul(b.x, a.y) - f_mul(a.x, b.y)) < 0)
	{
		current.left_z = game.points[game.walls[i].b];
		current.right_z = game.points[game.walls[i].a];
	}
	return (current);
}

t_cache_wall	switch_portals(t_cache_wall current, t_game game, size_t wall)
{
	t_fvec3	a;
	t_fvec3	b;
	size_t	sector;

	sector = find_sector_portals(game, wall);
	b.x = f_from_float((game.points[game.walls[wall].a].u
		+ game.points[game.walls[wall].b].u)
	/ 2 - game.sectors[sector].center.u);
	b.y = f_from_float((game.points[game.walls[wall].a].v
		+ game.points[game.walls[wall].b].v)
	/ 2 - game.sectors[sector].center.v);
	a.x = f_from_float(game.points[game.walls[wall].a].u
		- game.sectors[sector].center.u);
	a.y = f_from_float(game.points[game.walls[wall].a].v
		- game.sectors[sector].center.v);
	if ((f_mul(b.x, a.y) - f_mul(a.x, b.y)) > 0)
	{
		current.left_p = game.points[game.walls[wall].b];
		current.right_p = game.points[game.walls[wall].a];
	}
	return (current);
}
