/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:59:28 by hugo              #+#    #+#             */
/*   Updated: 2019/05/07 12:17:14 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game		create_material(t_game game)
{
	const t_mat	*old = game.materials;

	if ((game.materials = (t_mat *)realloc(game.materials, sizeof(t_mat) *
		(game.nmaterials + 1))) == NULL)
		return (game);
	if (game.materials == old)
		return (game);
	game = create_mat_update_materials((size_t)old, game);
	game = create_mat_update_walls((size_t)old, game);
	game = create_mat_update_portals((size_t)old, game);
	game = create_mat_update_sectors((size_t)old, game);
	game = create_mat_update_entities((size_t)old, game);
	game.materials[game.nmaterials] = game.materials[0];
	game.nmaterials++;
	return (game);
}