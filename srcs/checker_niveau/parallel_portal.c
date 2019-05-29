/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convex_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:43:33 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/08 16:43:57 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_check_sect	init_vector(t_game game, t_portal *portals, size_t cpt)
{
	t_check_sect data;

	data.ab = vec2_new(game.points[game.walls[portals[cpt].from_wall].b].u
		- game.points[game.walls[portals[cpt].from_wall].a].u,
		game.points[game.walls[portals[cpt].from_wall].b].v
		- game.points[game.walls[portals[cpt].from_wall].a].v);
	data.cd = vec2_new(game.points[game.walls[portals[cpt].to_wall].b].u
		- game.points[game.walls[portals[cpt].to_wall].a].u,
		game.points[game.walls[portals[cpt].to_wall].b].v
		- game.points[game.walls[portals[cpt].to_wall].a].v);
	return (data);
}

t_list				parallel_portal(t_portal *portals, size_t nportals,
t_game game)
{
	t_list			error;
	t_lvl_error		*elem;
	size_t			cpt;
	t_check_sect	data;

	cpt = -1;
	error = lnew(NULL);
	while (++cpt < nportals)
	{
		data = init_vector(game, portals, cpt);
		if ((data.ab.u * data.cd.v) - (data.cd.u * data.ab.v) != 0)
		{
			elem = (t_lvl_error *)safe_malloc(sizeof(t_lvl_error),
				"level_checker");
			init_error(elem);
			elem->elem.next = NULL;
			elem->portal = cpt;
			elem->error_type = PARALLEL_PORTAL;
			lpush(&error, (t_elem *)elem);
		}
	}
	return (error);
}
