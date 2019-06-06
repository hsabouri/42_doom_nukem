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

static t_lvl_error	check_sector_id(t_sector *sectors, size_t nsectors)
{
	t_lvl_error	error;
	size_t		cpt;

	cpt = 0;
	init_error(&error);
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

static t_lvl_error	check_sector_floor(t_sector *sectors, size_t nsectors,
t_check_mat mats)
{
	t_lvl_error	error;
	size_t		cpt;
	u_int32_t	index;

	cpt = 0;
	init_error(&error);
	while (cpt < nsectors)
	{
		index = id_from_p(sectors[cpt].floor_mat, mats.materials,
			sizeof(t_mat));
		if (index >= mats.nmaterials)
		{
			error.error_type = MATS_FLOOR_SECTOR;
			error.sector = cpt;
			return (error);
		}
		cpt++;
	}
	return (error);
}

static t_lvl_error	check_sector_ceil(t_sector *sectors, size_t nsectors,
t_check_mat mats)
{
	t_lvl_error	error;
	size_t		cpt;
	u_int32_t	index;

	cpt = 0;
	init_error(&error);
	while (cpt < nsectors)
	{
		index = id_from_p(sectors[cpt].ceiling_mat, mats.materials,
			sizeof(t_mat));
		if (index >= mats.nmaterials)
		{
			error.error_type = MATS_CEIL_SECTOR;
			error.sector = cpt;
			return (error);
		}
		cpt++;
	}
	return (error);
}

static u_int32_t	launch_check_sector_2(t_game game, t_check_mat mats,
t_env *env, char *errors_text[NBR_ERROR])
{
	t_lvl_error	error;

	error = check_sector_floor(game.sectors, game.nsectors, mats);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": sector ");
		ft_putnbr(error.sector);
		ft_putchar('\n');
		return (check_editor(env));
	}
	error = check_sector_ceil(game.sectors, game.nsectors, mats);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": sector ");
		ft_putnbr(error.sector);
		ft_putchar('\n');
		return (check_editor(env));
	}
	return (1);
}

u_int32_t			launch_check_sector(t_game game, t_check_mat mats,
t_env *env, char *errors_text[NBR_ERROR])
{
	t_lvl_error	error;

	error = check_wall_sector(game.sectors, game.nsectors, game.nwalls);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": sector ");
		ft_putnbr(error.sector);
		ft_putstr(", wall ");
		ft_putnbr(error.wall);
		ft_putchar('\n');
		return (check_editor(env));
	}
	error = check_sector_id(game.sectors, game.nsectors);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": sector ");
		ft_putnbr(error.sector);
		ft_putchar('\n');
		return (check_editor(env));
	}
	launch_check_sector_2(game, mats, env, errors_text);
	return (1);
}
