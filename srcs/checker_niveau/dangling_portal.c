/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dangling_portal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:39:36 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/22 13:54:16 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_list			dangling_portal_wall(t_portal *portals, size_t nportals,\
t_game game)
{
	t_list		error;
	t_lvl_error	*elem;
	int			cpt;

	error = lnew(NULL);
	cpt = -1;
	while (++cpt < (int)nportals)
	{
		if (game.walls[portals[cpt].to_wall].portal != cpt
			|| game.walls[portals[cpt].from_wall].portal != cpt)
		{
			elem = (t_lvl_error *)safe_malloc(sizeof(t_lvl_error),
				"level_checker");
			init_error(elem);
			elem->elem.next = NULL;
			elem->error_type = DANGLING_PORTAL_WALL;
			elem->portal = cpt;
			if (game.walls[portals[cpt].to_wall].portal != cpt)
				elem->wall = portals[cpt].to_wall;
			else
				elem->wall = portals[cpt].from_wall;
			lpush(&error, (t_elem *)elem);
		}
	}
	return (error);
}

static t_list	*check_second_wall(t_portal *portals, t_game game,
size_t nportals, t_list *error)
{
	int			cpt;
	t_lvl_error	*elem;
	size_t		end_wall_to;

	cpt = 0;
	while (cpt < (int)nportals)
	{
		end_wall_to = game.sectors[portals[cpt].to_sector].start
			+ game.sectors[portals[cpt].to_sector].number;
		if (portals[cpt].to_wall < game.sectors[portals[cpt].to_sector].start
			|| portals[cpt].to_wall >= end_wall_to)
		{
			elem = (t_lvl_error *)safe_malloc(sizeof(t_lvl_error),
				"level_checker");
			init_error(elem);
			elem->elem.next = NULL;
			elem->portal = cpt;
			elem->error_type = DANGLING_PORTAL_SECTOR;
			elem->wall = portals[cpt].to_wall;
			lpush(error, (t_elem *)elem);
		}
		cpt++;
	}
	return (error);
}

static t_list	*check_first_wall(t_portal *portals, t_game game,
size_t nportals, t_list *error)
{
	t_lvl_error	*elem;
	int			i;
	size_t		end_wall_from;

	i = -1;
	while (++i < (int)nportals)
	{
		end_wall_from = game.sectors[portals[i].from_sector].start
			+ game.sectors[portals[i].from_sector].number;
		if (portals[i].from_wall <
			game.sectors[portals[i].from_sector].start
			|| portals[i].from_wall >= end_wall_from)
		{
			elem = (t_lvl_error *)safe_malloc(sizeof(t_lvl_error),
				"level_checker");
			init_error(elem);
			elem->error_type = DANGLING_PORTAL_SECTOR;
			elem->elem.next = NULL;
			elem->portal = i;
			elem->wall = portals[i].from_wall;
			lpush(error, (t_elem *)elem);
		}
	}
	return (error);
}

t_list			dangling_portal_sector(t_portal *portals, size_t nportals,
t_game game)
{
	t_list		error;

	error = lnew(NULL);
	check_first_wall(portals, game, nportals, &error);
	check_second_wall(portals, game, nportals, &error);
	return (error);
}
