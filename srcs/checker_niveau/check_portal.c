/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:04:56 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/22 14:03:28 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_lvl_error	sector_portal(t_portal *portals, size_t nportals,
size_t nsectors)
{
	t_lvl_error	error;
	size_t		cpt;

	cpt = 0;
	init_error(&error);
	while (cpt < nportals)
	{
		if (portals[cpt].from_sector > nsectors
			|| portals[cpt].to_sector > nsectors)
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

static t_lvl_error	wall_portal(t_portal *portals, size_t nportals,
size_t nwalls)
{
	t_lvl_error	error;
	size_t		cpt;

	cpt = 0;
	init_error(&error);
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

u_int32_t			launch_check_portal(t_game game, t_env *env,
char *errors_text[NBR_ERROR])
{
	t_lvl_error	error;

	error = sector_portal(game.portals, game.nportals, game.nsectors);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": portal ");
		ft_putnbr(error.portal);
		ft_putstr(", sector ");
		ft_putnbr(error.sector);
		ft_putchar('\n');
		return (check_editor(env));
	}
	error = wall_portal(game.portals, game.nportals, game.nwalls);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": portal ");
		ft_putnbr(error.portal);
		ft_putstr(", wall ");
		ft_putnbr(error.wall);
		ft_putchar('\n');
		return (check_editor(env));
	}
	return (1);
}
