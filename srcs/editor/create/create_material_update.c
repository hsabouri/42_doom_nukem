/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_material_update.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:59:18 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/07 12:29:14 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

#define ID(old, start) ((size_t)old - (size_t)start) / sizeof(t_mat)

t_game	create_mat_update_materials(size_t a_old, t_game game)
{
	size_t	i;
	t_mat	curr;

	i = 0;
	while (i < game.nmaterials)
	{
		curr = game.materials[i];
		if (curr.overlay != NULL)
		{
			curr.overlay = &game.materials[ID(curr.overlay, a_old)];
			game.materials[i] = curr;
		}
		i++;
	}
	return (game);
}

t_game	create_mat_update_walls(size_t a_old, t_game game)
{
	size_t	i;
	t_wall	c;

	i = 0;
	while (i < game.nwalls)
	{
		c = game.walls[i];
		c.mat = &game.materials[ID(c.mat, a_old)];
		game.walls[i] = c;
		i++;
	}
	return (game);
}

t_game	create_mat_update_sectors(size_t a_old, t_game g)
{
	size_t		i;
	t_sector	c;

	i = 0;
	while (i < g.nsectors)
	{
		c = g.sectors[i];
		c.floor_mat = &g.materials[ID(c.floor_mat, a_old)];
		c.ceiling_mat = &g.materials[ID(c.ceiling_mat, a_old)];
		g.sectors[i] = c;
		i++;
	}
	return (g);
}

t_game	create_mat_update_portals(size_t a_old, t_game game)
{
	size_t		i;
	t_portal	curr;

	i = 0;
	while (i < game.nportals)
	{
		curr = game.portals[i];
		if (curr.mat != NULL)
		{
			curr.mat = &game.materials[ID(curr.mat, a_old)];
			game.portals[i] = curr;
		}
		i++;
	}
	return (game);
}

t_game	create_mat_update_entities(size_t a_old, t_game game)
{
	size_t		i;
	size_t		j;
	t_mat		**curr;

	i = 0;
	while (i < game.nentities)
	{
		j = 0;
		while ((curr = (t_mat **)anth(&game.entities[i].mat, j)) != NULL)
		{
			*curr = &game.materials[ID(*curr, a_old)];
			j++;
		}
		i++;
	}
	return (game);
}

