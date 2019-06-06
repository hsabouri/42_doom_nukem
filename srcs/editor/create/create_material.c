/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:59:28 by hugo              #+#    #+#             */
/*   Updated: 2019/05/11 15:20:32 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game		create_material(size_t selected, t_game game)
{
	const t_mat	*old = game.materials;

	if ((game.materials = (t_mat *)realloc(game.materials, sizeof(t_mat)
		* (game.nmaterials + 1))) == NULL)
		return (game);
	if (game.materials == old)
	{
		game.materials[game.nmaterials] = game.materials[selected];
		game.materials[game.nmaterials].frozen = 0;
		game.nmaterials++;
		return (game);
	}
	game = create_mat_update_materials((size_t)old, game);
	game = create_mat_update_walls((size_t)old, game);
	game = create_mat_update_portals((size_t)old, game);
	game = create_mat_update_sectors((size_t)old, game);
	game = create_mat_update_multi_mats((size_t)old, game);
	game.materials[game.nmaterials] = game.materials[selected];
	game.materials[game.nmaterials].frozen = 0;
	game.nmaterials++;
	return (game);
}
