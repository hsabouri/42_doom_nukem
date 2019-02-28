/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:22:13 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/25 11:22:15 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_lvl_error	check_wall_sector(t_sector *sectors, t_lvl_error error,\
size_t nsectors, size_t nwalls)
{
	size_t	cpt;
	size_t	nbr_walls;

	cpt = 0;
	while (cpt < nsectors)
	{
		nbr_walls = sectors[cpt].start + sectors[cpt].number;
		if (sectors[cpt].start > nwalls || sectors[cpt].number > nwalls ||
			nbr_walls > nwalls)
		{
			error.sector = cpt;
			if (sectors[cpt].start > nwalls)
				error = (t_lvl_error) {.error_type = WALL_START_SECTOR,
				.wall = sectors[cpt].start};
			else
				error = (t_lvl_error) {.error_type =
					(sectors[cpt].number > nwalls) ?
					WALL_END_SECTOR : NUMBER_WALLS_SECTOR,
					.wall = (ssize_t)(sectors[cpt].number)};
			return (error);
		}
		cpt++;
	}
	return (error);
}

t_lvl_error	check_sector_id(t_sector *sectors, t_lvl_error error,\
size_t nsectors)
{
	size_t	cpt;

	cpt = 0;
	while (cpt < nsectors)
	{
		if (sectors[cpt].sector_id > nsectors)
		{
			error.error_type = ID_SECTOR;
			error.sector = cpt;
			return (error);
		}
		cpt++;
	}
	return (error);
}

t_lvl_error	check_sector_floor(t_sector *sectors, t_lvl_error error,\
size_t nsectors, t_check_mat mats)
{
	size_t		cpt;
	u_int32_t	index;

	cpt = 0;
	while (cpt < nsectors)
	{
		index = id_from_p(sectors[cpt].floor_mat, mats.materials,
			sizeof(t_mat));
		if (index > mats.nmaterials)
		{
			error.error_type = MATS_FLOOR_SECTOR;
			error.sector = cpt;
			return (error);
		}
		cpt++;
	}
	return (error);
}

t_lvl_error	check_sector_ceil(t_sector *sectors, t_lvl_error error,\
size_t nsectors, t_check_mat mats)
{
	size_t		cpt;
	u_int32_t	index;

	cpt = 0;
	while (cpt < nsectors)
	{
		index = id_from_p(sectors[cpt].ceiling_mat, mats.materials,
			sizeof(t_mat));
		if (index > mats.nmaterials)
		{
			error.error_type = MATS_CEIL_SECTOR;
			error.sector = cpt;
			return (error);
		}
		cpt++;
	}
	return (error);
}

u_int32_t	launch_check_sector(t_lvl_error error, t_game game,\
char *errors_text[NBR_ERROR], t_check_mat mats)
{
	error = check_wall_sector(game.sectors, error, game.nsectors, game.nwalls);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: sector %zu, wall %zu\n", errors_text[error.error_type],
			error.sector, error.wall);
		return (0);
	}
	error = check_sector_id(game.sectors, error, game.nsectors);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: sector %zu\n", errors_text[error.error_type], error.sector);
		return (0);
	}
	error = check_sector_floor(game.sectors, error, game.nsectors, mats);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: sector %zu\n", errors_text[error.error_type], error.sector);
		return (0);
	}
	error = check_sector_ceil(game.sectors, error, game.nsectors, mats);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: sector %zu\n", errors_text[error.error_type], error.sector);
		return (0);
	}
	return (1);
}
