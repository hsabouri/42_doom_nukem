/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sector_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <iporsenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:56:49 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/15 10:59:05 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_lvl_error		check_wall_sector(t_sector *sectors, size_t nsectors,
size_t nwalls)
{
	t_lvl_error	error;
	size_t		cpt;
	size_t		nbr_walls;

	cpt = -1;
	init_error(&error);
	while (++cpt < nsectors)
	{
		nbr_walls = sectors[cpt].start + sectors[cpt].number;
		if (sectors[cpt].start > nwalls || sectors[cpt].number > nwalls
			|| nbr_walls > nwalls)
		{
			error.sector = cpt;
			if (sectors[cpt].start > nwalls)
				error = (t_lvl_error) {.error_type = WALL_START_SECTOR,
				.wall = sectors[cpt].start};
			else
				error = (t_lvl_error) {.error_type = (sectors[cpt].number
					> nwalls) ? WALL_END_SECTOR : NUMBER_WALLS_SECTOR,
					.wall = (ssize_t)(sectors[cpt].number)};
			return (error);
		}
	}
	return (error);
}

t_list			height_sector(t_sector *sectors, size_t nsectors)
{
	t_list		error;
	t_lvl_error	*elem;
	size_t		cpt;

	cpt = 0;
	error = lnew(NULL);
	while (cpt < nsectors)
	{
		if ((sectors[cpt].ceiling.z - sectors[cpt].floor.z) < 0)
		{
			elem = (t_lvl_error *)safe_malloc(sizeof(t_lvl_error),
				"level_checker");
			init_error(elem);
			elem->elem.next = NULL;
			elem->error_type = HEIGHT_SECTOR;
			elem->sector = cpt;
			lpush(&error, (t_elem *)elem);
		}
		cpt++;
	}
	return (error);
}
