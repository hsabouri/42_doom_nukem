/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 14:42:23 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/24 14:42:25 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_lvl_error	check_point_wall(t_wall *walls, size_t nwalls,
size_t npoints)
{
	t_lvl_error	error;
	size_t		cpt;

	cpt = 0;
	init_error(&error);
	while (cpt < nwalls)
	{
		if (walls[cpt].a > npoints || walls[cpt].b > npoints)
		{
			error.error_type = POINTS_WALL;
			error.wall = cpt;
			if (walls[cpt].a > npoints)
				error.point = walls[cpt].a;
			else
				error.point = walls[cpt].b;
			return (error);
		}
		cpt++;
	}
	return (error);
}

static t_lvl_error	check_portal_wall(t_wall *walls, size_t nwalls,
size_t nportals)
{
	t_lvl_error	error;
	size_t		cpt;

	cpt = 0;
	init_error(&error);
	while (cpt < nwalls)
	{
		if (walls[cpt].portal > (int32_t)nportals || walls[cpt].portal < -1)
		{
			error.error_type = POINT_PORTAL_WALL;
			error.wall = cpt;
			error.portal = walls[cpt].portal;
			return (error);
		}
		cpt++;
	}
	return (error);
}

static t_lvl_error	check_mats_wall(t_wall *walls, size_t nwalls,
t_check_mat mats)
{
	t_lvl_error	error;
	size_t		cpt;
	u_int32_t	index;

	cpt = 0;
	init_error(&error);
	while (cpt < nwalls)
	{
		index = id_from_p(walls[cpt].mat, mats.materials, sizeof(t_mat));
		if (index >= mats.nmaterials)
		{
			error.error_type = MATS_WALL;
			error.wall = cpt;
			return (error);
		}
		cpt++;
	}
	return (error);
}

static u_int32_t	launch_check_wall_2(t_game game, t_check_mat mats,
t_env *env, char *errors_text[NBR_ERROR])
{
	t_lvl_error error;

	error = check_portal_wall(game.walls, game.nwalls, game.nportals);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": wall ");
		ft_putnbr(error.wall);
		ft_putstr(", portal ");
		ft_putnbr(error.portal);
		ft_putchar('\n');
		return (check_editor(env));
	}
	error = check_mats_wall(game.walls, game.nwalls, mats);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": wall ");
		ft_putnbr(error.wall);
		ft_putchar('\n');
		return (check_editor(env));
	}
	return (1);
}

u_int32_t			launch_check_wall(t_game game, t_check_mat mats, t_env *env,
char *errors_text[NBR_ERROR])
{
	t_lvl_error	error;

	error = check_point_wall(game.walls, game.nwalls, game.npoints);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": wall ");
		ft_putnbr(error.wall);
		ft_putstr(", point ");
		ft_putnbr(error.point);
		ft_putchar('\n');
		return (check_editor(env));
	}
	launch_check_wall_2(game, mats, env, errors_text);
	return (1);
}
