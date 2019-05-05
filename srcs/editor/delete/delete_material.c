/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:09:46 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/05 14:46:31 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game	delete_material(size_t mat, t_game game)
{
	// Need to readdress every material in every object of the game gheee
	if (mat >= game.nmaterials)
		return (game);
	if (!(game.materials =\
	array_close(game.materials, mat, game.nmaterials, sizeof(t_mat))))
		return (game);
	game.nmaterials--;
	del_update_materials(mat, game);
	del_update_walls(-1, -1, mat, game);
	del_update_sectors(-1, mat, -1, game);
	del_update_portals(-1, -1, -1, mat, game);
	return (game);
}
