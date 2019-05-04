/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:09:46 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/04 18:15:30 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game	delete_material(size_t mat, t_game game)
{
	if (mat >= game.nmaterials)
		return (game);
	if (!(game.materials =\
	array_close(game.materials, mat, game.nmaterials, sizeof(t_mat))))
		return (game);
	game.nmaterials--;
	return (game);
}
