/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convex_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:43:33 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/08 16:43:57 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static void		create_vector(t_vec2 *ab, t_vec2 *cd, t_game game,\
t_check_sect data)
{
	if (data.start != data.end - 1)
	{
		*ab = vec2_new(game.points[game.walls[data.start].b].u -
			game.points[game.walls[data.start].a].u,
			game.points[game.walls[data.start].b].v -
			game.points[game.walls[data.start].a].v);
		*cd = vec2_new(game.points[game.walls[data.start + 1].b].u -
			game.points[game.walls[data.start + 1].a].u,
			game.points[game.walls[data.start + 1].b].v -
			game.points[game.walls[data.start + 1].a].v);
	}
	else
	{
		*ab = vec2_new(game.points[game.walls[data.start].b].u -
			game.points[game.walls[data.start].a].u,
			game.points[game.walls[data.start].b].v -
			game.points[game.walls[data.start].a].v);
		*cd = vec2_new(game.points[game.walls[data.first].b].u -
			game.points[game.walls[data.first].a].u,
			game.points[game.walls[data.first].b].v -
			game.points[game.walls[data.first].a].v);
	}
}

static t_list	*check_angle(t_check_sect data, size_t cpt, t_list *error)
{
	t_lvl_error	*elem;

	if (data.sign > 0)
	{
		if (data.angle < 0)
		{
			elem = (t_lvl_error *)malloc(sizeof(t_lvl_error));
			elem->elem.next = NULL;
			elem->error_type = CONCAVE_SECTOR;
			elem->sector = cpt;
			lpush(error, (t_elem *)elem);
		}
	}
	else
	{
		if (data.angle > 0)
		{
			elem = (t_lvl_error *)malloc(sizeof(t_lvl_error));
			elem->elem.next = NULL;
			elem->error_type = CONCAVE_SECTOR;
			elem->sector = cpt;
			lpush(error, (t_elem *)elem);
		}
	}
	return (error);
}

t_list			convex_sector(t_sector *sectors, size_t nsectors, t_game game)
{
	t_list			error;
	size_t			cpt;
	t_check_sect	data;

	cpt = 0;
	error = lnew(NULL);
	while (cpt < nsectors)
	{
		data.first = sectors[cpt].start;
		data.start = data.first;
		data.end = data.start + sectors[cpt].number;
		create_vector(&data.ab, &data.cd, game, data);
		data.sign = (vec2_cross(data.ab, data.cd).z > 0) ? 1 : -1;
		while (++data.start < data.end)
		{
			create_vector(&data.ab, &data.cd, game, data);
			data.angle = vec2_cross(data.ab, data.cd).z;
			check_angle(data, cpt, &error);
		}
		cpt++;
	}
	return (error);
}

t_list			parallel_portal(t_portal *portals, size_t nportals, t_game game)
{
	t_list			error;
	t_lvl_error		*elem;
	size_t			cpt;
	t_check_sect	data;

	cpt = -1;
	error = lnew(NULL);
	while (++cpt < nportals)
	{
		data.ab = vec2_new(game.points[game.walls[portals[cpt].from_wall].b].u -
			game.points[game.walls[portals[cpt].from_wall].a].u,
			game.points[game.walls[portals[cpt].from_wall].b].v -
			game.points[game.walls[portals[cpt].from_wall].a].v);
		data.cd = vec2_new(game.points[game.walls[portals[cpt].to_wall].b].u -
			game.points[game.walls[portals[cpt].to_wall].a].u,
			game.points[game.walls[portals[cpt].to_wall].b].v -
			game.points[game.walls[portals[cpt].to_wall].a].v);
		if ((data.ab.u * data.cd.v) - (data.cd.u * data.ab.v) != 0)
		{
			elem = (t_lvl_error *)malloc(sizeof(t_lvl_error));
			*elem = (t_lvl_error) {.elem.next = NULL, .portal = cpt,
				.error_type = PARALLEL_PORTAL};
			lpush(&error, (t_elem *)elem);
		}
	}
	return (error);
}
