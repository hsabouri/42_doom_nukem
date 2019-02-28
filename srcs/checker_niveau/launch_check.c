/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:20:52 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/23 16:20:53 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	init_error(t_lvl_error *error)
{
	error->error_type = NO_ERROR;
	error->point = -1;
	error->wall = -1;
	error->portal = -1;
	error->sector = -1;
	error->mats = -1;
}

void	init_errors_text(char *errors_text[NBR_ERROR])
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
	errors_text[13] = "too much wall in sector";
	errors_text[14] = "open sector";
	errors_text[15] = "height of sector too small";
	errors_text[16] = "height of adjacent sector too small";
	errors_text[17] = "concave sector";
	errors_text[18] = "entity spawn outside the world";
	errors_text[19] = "missing sector in portal";
	errors_text[20] = "missing wall in portal";
	errors_text[21] = "missing id in sector";
	errors_text[22] = "missing overlay in sector";
	errors_text[23] = "portals aren't parallel";
}

void	launch_check(t_game game)
{
	t_lvl_error	error;
	char		*errors_text[NBR_ERROR];
	t_list		error_list;
	t_list		current;
	t_lvl_error	*buh;
	t_check_mat	mats;

	init_error(&error);
	init_errors_text(errors_text);
	mats.nmaterials = game.nmaterials;
	mats.materials = game.materials;
	if (launch_check_wall(error, game, errors_text, mats) == 1 &&
		launch_check_portal(error, game, errors_text) == 1 &&
		launch_check_sector(error, game, errors_text, mats) == 1 &&
		launch_check_mats(error, game, errors_text, mats) == 1)
		printf("no blocking errors\n");
	error_list = lnew(NULL);
	current = check_max_wall(game.sectors, game.nsectors);
	error_list = *ljoin(&error_list, &current);
	current = dangling_portal_wall(game.portals, game.nportals, game);
	error_list = *ljoin(&error_list, &current);
	current = dangling_portal_sector(game.portals, game.nportals, game);
	error_list = *ljoin(&error_list, &current);
	current = open_sector(game.sectors, game.nsectors, game);
	error_list = *ljoin(&error_list, &current);
	current = height_sector(game.sectors, game.nsectors);
	error_list = *ljoin(&error_list, &current);
	current = height_next_sector(game.sectors, game.nsectors, game);
	error_list = *ljoin(&error_list, &current);
	current = convex_sector(game.sectors, game.nsectors, game);
	error_list = *ljoin(&error_list, &current);
	current = parallel_portal(game.portals, game.nportals, game);
	error_list = *ljoin(&error_list, &current);
	while ((buh = (t_lvl_error *)lnext(&error_list)))
	{
		printf("%s: point: %ld, wall: %ld, portal: %d, sector: %ld, mat: %ld\n",
			errors_text[buh->error_type], buh->point, buh->wall, buh->portal,
			buh->sector, buh->mats);
	}
}
