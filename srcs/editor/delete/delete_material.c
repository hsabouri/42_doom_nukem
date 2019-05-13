/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:09:46 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/11 15:20:40 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game	delete_material(size_t mat, t_game game)
{
	const size_t	old = (size_t)game.materials;
	t_mat			*new;

	if (mat >= game.nmaterials)
		return (game);
	new = array_close(game.materials, mat, game.nmaterials, sizeof(t_mat));
	if (!new)
		return (game);
	game.materials = new;
	game.nmaterials--;
	game = del_mat_update_materials(mat, old, game);
	game = del_mat_update_walls(mat, old, game);
	game = del_mat_update_portals(mat, old, game);
	game = del_mat_update_sectors(mat, old, game);
	game = del_mat_update_multi_mats(mat, old, game);
	return (game);
}
