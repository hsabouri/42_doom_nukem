/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:04:56 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/24 16:04:58 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_lvl_error	check_point_portal(t_portal *portals, t_lvl_error error,\
size_t nportals, size_t npoints)
{
	size_t	cpt;

	cpt = 0;
	while (cpt < nportals)
	{
		if (portals[cpt].a > npoints || portals[cpt].b > npoints)
		{
			error.error_type = POINTS_PORTAL;
			error.portal = cpt;
			if (portals[cpt].a > npoints)
				error.point = portals[cpt].a;
			else
				error.point = portals[cpt].b;
			return (error);
		}
		cpt++;
	}
	return (error);
}

t_lvl_error	sector_portal(t_portal *portals, t_lvl_error error,\
size_t nportals, size_t nsectors)
{
	size_t	cpt;

	cpt = 0;
	while (cpt < nportals)
	{
		if (portals[cpt].from_sector > nsectors ||
			portals[cpt].to_sector > nsectors)
		{
			error.error_type = SECTOR_PORTAL;
			error.portal = cpt;
			if (portals[cpt].from_sector > nsectors)
				error.sector = portals[cpt].from_sector;
			else
				error.sector = portals[cpt].to_sector;
			return (error);
		}
		cpt++;
	}
	return (error);
}

t_lvl_error	wall_portal(t_portal *portals, t_lvl_error error,\
size_t nportals, size_t nwalls)
{
	size_t	cpt;

	cpt = 0;
	while (cpt < nportals)
	{
		if (portals[cpt].from_wall > nwalls || portals[cpt].to_wall > nwalls)
		{
			error.error_type = SECTOR_PORTAL;
			error.portal = cpt;
			if (portals[cpt].from_wall > nwalls)
				error.wall = portals[cpt].from_wall;
			else
				error.wall = portals[cpt].to_wall;
			return (error);
		}
		cpt++;
	}
	return (error);
}

u_int32_t	launch_check_portal(t_lvl_error error, t_game game,\
char *errors_text[NBR_ERROR], t_env *env)
{
	error = check_point_portal(game.portals, error, game.nportals,
		game.npoints);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: portal %d, point %d\n", errors_text[error.error_type],
			error.portal, error.point);
		return (check_editor(env));
	}
	error = sector_portal(game.portals, error, game.nportals, game.nsectors);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: portal %d, sector %d\n", errors_text[error.error_type],
			error.portal, error.sector);
		return (check_editor(env));

	}
	error = wall_portal(game.portals, error, game.nportals, game.nwalls);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: portal %d, wall %d\n", errors_text[error.error_type],
			error.portal, error.wall);
		return (check_editor(env));
	}
	return (1);
}
