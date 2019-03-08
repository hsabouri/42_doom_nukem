/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sector_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:56:49 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/08 16:35:12 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_list	*browse_wall(t_game game, t_check_sect data, size_t cpt,\
t_list *error)
{
	t_lvl_error	*elem;

	if (game.walls[data.start].a != data.previous && data.start != data.end)
	{
		elem = (t_lvl_error *)malloc(sizeof(t_lvl_error));
		elem->elem.next = NULL;
		elem->error_type = OPEN_SECTOR;
		elem->sector = cpt;
		elem->wall = data.start;
		lpush(error, (t_elem *)elem);
	}
	if (data.start == data.end - 1 && game.walls[data.start].b != data.first)
	{
		elem = (t_lvl_error *)malloc(sizeof(t_lvl_error));
		elem->elem.next = NULL;
		elem->error_type = OPEN_SECTOR;
		elem->sector = cpt;
		elem->wall = data.start;
		lpush(error, (t_elem *)elem);
	}
	return (error);
}

t_list			open_sector(t_sector *sectors, size_t nsectors, t_game game)
{
	t_list			error;
	t_check_sect	data;
	size_t			cpt;

	cpt = 0;
	error = lnew(NULL);
	while (cpt < nsectors)
	{
		data.start = sectors[cpt].start;
		data.end = data.start + sectors[cpt].number;
		data.first = game.walls[data.start].a;
		data.previous = game.walls[data.start].b;
		while (++data.start < data.end)
		{
			browse_wall(game, data, cpt, &error);
			data.previous = game.walls[data.start].b;
		}
		cpt++;
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
		if ((sectors[cpt].ceiling - sectors[cpt].floor) < 0.1)
		{
			elem = (t_lvl_error *)malloc(sizeof(t_lvl_error));
			elem->elem.next = NULL;
			elem->error_type = HEIGHT_SECTOR;
			elem->sector = cpt;
			lpush(&error, (t_elem *)elem);
		}
		cpt++;
	}
	return (error);
}

static t_list	*browse_next_sector(size_t cpt, size_t start, t_game game,\
t_list *error)
{
	t_lvl_error	*elem;
	size_t		sector_out;

	sector_out = (game.portals[game.walls[start].portal].from_sector == cpt) ?\
		game.portals[game.walls[start].portal].to_sector :
		game.portals[game.walls[start].portal].from_sector;
	if (game.sectors[sector_out].ceiling - game.sectors[cpt].floor < 0.1)
	{
		elem = (t_lvl_error *)malloc(sizeof(t_lvl_error));
		elem->elem.next = NULL;
		elem->error_type = HEIGHT_SECTOR_NEXT;
		elem->sector = cpt;
		lpush(error, (t_elem *)elem);
	}
	return (error);
}

t_list			height_next_sector(t_sector *sectors, size_t nsectors,\
t_game game)
{
	t_list	error;
	size_t	cpt;
	size_t	start;
	size_t	end;

	cpt = 0;
	error = lnew(NULL);
	while (cpt < nsectors)
	{
		start = sectors[cpt].start;
		end = start + sectors[cpt].number;
		while (start < end)
		{
			if (game.walls[start].portal > -1)
				browse_next_sector(cpt, start, game, &error);
			start++;
		}
		cpt++;
	}
	return (error);
}
