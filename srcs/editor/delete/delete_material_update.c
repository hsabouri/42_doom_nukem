/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_material_update.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:59:18 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/11 15:17:48 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

#define ID(old, start) ((size_t)old - (size_t)start) / sizeof(t_mat)

t_game	del_mat_update_materials(size_t mat, size_t a_old, t_game game)
{
	size_t	i;
	t_mat	curr;

	i = 0;
	while (i < game.nmaterials)
	{
		curr = game.materials[i];
		if (curr.overlay != NULL)
		{
			if ((size_t)curr.overlay > mat * sizeof(t_mat) + a_old)
				curr.overlay = &game.materials[ID(curr.overlay, a_old) - 1];
			else if ((size_t)curr.overlay == mat * sizeof(t_mat) + a_old)
				curr.overlay = NULL;
			else
				curr.overlay = &game.materials[ID(curr.overlay, a_old)];
			game.materials[i] = curr;
		}
		i++;
	}
	return (game);
}

t_game	del_mat_update_walls(size_t mat, size_t a_old, t_game game)
{
	size_t	i;
	t_wall	c;

	i = 0;
	while (i < game.nwalls)
	{
		c = game.walls[i];
		if ((size_t)c.mat > mat * sizeof(t_mat) + a_old)
			c.mat = &game.materials[ID(c.mat, a_old) - 1];
		else if ((size_t)c.mat == mat * sizeof(t_mat) + a_old)
			c.mat = game.materials;
		else
			c.mat = &game.materials[ID(c.mat, a_old)];
		game.walls[i] = c;
		i++;
	}
	return (game);
}

t_game	del_mat_update_sectors(size_t mat, size_t a_old, t_game g)
{
	size_t		i;
	t_sector	c;

	i = 0;
	while (i < g.nsectors)
	{
		c = g.sectors[i];
		if ((size_t)c.floor_mat > mat * sizeof(t_mat) + a_old)
			c.floor_mat = &g.materials[ID(c.floor_mat, a_old) - 1];
		else if ((size_t)c.floor_mat == mat * sizeof(t_mat) + a_old)
			c.floor_mat = g.materials;
		else
			c.floor_mat = &g.materials[ID(c.floor_mat, a_old)];
		if ((size_t)c.ceiling_mat > mat * sizeof(t_mat) + a_old)
			c.ceiling_mat = &g.materials[ID(c.ceiling_mat, a_old) - 1];
		else if ((size_t)c.ceiling_mat == mat * sizeof(t_mat) + a_old)
			c.ceiling_mat = g.materials;
		else
			c.ceiling_mat = &g.materials[ID(c.ceiling_mat, a_old)];
		g.sectors[i] = c;
		i++;
	}
	return (g);
}

t_game	del_mat_update_portals(size_t mat, size_t a_old, t_game game)
{
	size_t		i;
	t_portal	curr;

	i = 0;
	while (i < game.nportals)
	{
		curr = game.portals[i];
		if (curr.mat != NULL)
		{
			if ((size_t)curr.mat > mat * sizeof(t_mat) + a_old)
				curr.mat = &game.materials[ID(curr.mat, a_old) - 1];
			else if ((size_t)curr.mat == mat * sizeof(t_mat) + a_old)
				curr.mat = NULL;
			else
				curr.mat = &game.materials[ID(curr.mat, a_old)];
			game.portals[i] = curr;
		}
		i++;
	}
	return (game);
}

t_game	del_mat_update_multi_mats(size_t mat, size_t a_old, t_game game)
{
	size_t		i;
	size_t		j;
	t_mat		**curr;

	i = 0;
	while (i < game.nmulti_mats)
	{
		j = 0;
		while ((curr = (t_mat **)anth(&game.multi_mats[i], j)) != NULL)
		{
			if ((size_t)*curr > mat * sizeof(t_mat) + a_old)
				*curr = &game.materials[ID(*curr, a_old) - 1];
			else if ((size_t)*curr == mat * sizeof(t_mat) + a_old)
				*curr = game.materials;
			else
				*curr = &game.materials[ID(*curr, a_old)];
			j++;
		}
		i++;
	}
	return (game);
}
