/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:20:52 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/05 10:15:15 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static void	display_2(t_lvl_error *display, char *errors_text[NBR_ERROR])
{
	ft_putstr(errors_text[display->error_type]);
	if (display->sector != -1)
	{
		ft_putstr(": sector ");
		ft_putnbr(display->sector);
	}
	if (display->mats != -1)
	{
		ft_putstr(": material ");
		ft_putnbr(display->mats);
	}
	if (display->multi_mats != -1)
	{
		ft_putstr(": multi_mats ");
		ft_putnbr(display->multi_mats);
	}
	if (display->entities != -1)
	{
		ft_putstr(": entity ");
		ft_putnbr(display->entities);
	}
	ft_putchar('\n');
}

static void	display_no_blocking_error(t_list error_list,
char *errors_text[NBR_ERROR])
{
	t_lvl_error	*display;

	while ((display = (t_lvl_error *)lshift(&error_list)))
	{
		if (display->error_type != NO_ERROR)
		{
			display_2(display, errors_text);
			if (display->point != -1)
			{
				ft_putstr(": point ");
				ft_putnbr(display->point);
			}
			if (display->wall != -1)
			{
				ft_putstr(": wall ");
				ft_putnbr(display->wall);
			}
			if (display->portal != -1)
			{
				ft_putstr(": portal ");
				ft_putnbr(display->portal);
			}
		}
		free(display);
	}
}

static void	init_errors_text(char *errors_text[NBR_ERROR])
{
	errors_text[0] = "no error detected";
	errors_text[1] = "missing point in wall";
	errors_text[2] = "missing portal in wall";
	errors_text[3] = "missing material in wall";
	errors_text[4] = "missing point in portal";
	errors_text[5] = "dangling portal, wall doesn't pointed to the portal";
	errors_text[6] = "dangling portal, wall doesn't belong to any sector";
	errors_text[7] = "missing wall start in sector";
	errors_text[8] = "missing wall end in sector";
	errors_text[9] = "too much walls in sector";
	errors_text[10] = "missing material floor in sector";
	errors_text[11] = "missing material ceiling in sector";
	errors_text[12] = "missing texture in material";
	errors_text[13] = "open sector";
	errors_text[14] = "height of sector too small";
	errors_text[15] = "height of adjacent sector too small";
	errors_text[16] = "entity spawn outside the world";
	errors_text[17] = "missing sector in portal";
	errors_text[18] = "missing wall in portal";
	errors_text[19] = "missing id in sector";
	errors_text[20] = "missing overlay in sector";
	errors_text[21] = "portals aren't parallel";
	errors_text[22] = "missing multi_mat of entity";
	errors_text[23] = "bad sector_id of entity";
	errors_text[24] = "missing mat in multi_mat";
}

static void	check_no_blocking(char *errors_text[NBR_ERROR], t_game game)
{
	t_list	error_list;
	t_list	current;

	error_list = lnew(NULL);
	current = dangling_portal_wall(game.portals, game.nportals, game);
	error_list = *ljoin(&error_list, &current);
	current = dangling_portal_sector(game.portals, game.nportals, game);
	error_list = *ljoin(&error_list, &current);
	current = height_sector(game.sectors, game.nsectors);
	error_list = *ljoin(&error_list, &current);
	current = parallel_portal(game.portals, game.nportals, game);
	error_list = *ljoin(&error_list, &current);
	current = sector_entity(game.entities, game.nentities, game);
	error_list = *ljoin(&error_list, &current);
	display_no_blocking_error(error_list, errors_text);
}

int32_t		launch_check(t_env *env, t_game game)
{
	t_lvl_error	error;
	char		*errors_text[NBR_ERROR];
	t_check_mat	mats;

	init_error(&error);
	init_errors_text(errors_text);
	mats.nmaterials = game.nmaterials;
	mats.materials = game.materials;
	if (launch_check_wall(game, mats, env, errors_text) == 0
		|| launch_check_portal(game, env, errors_text) == 0
		|| launch_check_sector(game, mats, env, errors_text) == 0
		|| launch_check_mats(game, mats, env, errors_text) == 0
		|| launch_check_entities(game, env, errors_text) == 0)
		return (0);
	ft_putstr("no blocking errors");
	ft_putchar('\n');
	check_no_blocking(errors_text, game);
	ft_putchar('\n');
	return (1);
}
