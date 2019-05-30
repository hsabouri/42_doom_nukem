/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mat_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:51:39 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/30 16:51:48 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_mat	*init_mat_6(t_mat *materials, t_game *game)
{
	t_mat tmp;

	tmp = (t_mat) {.pos = fvec2_new(0, 0),
		.sca = fvec2_new(f_from_int(2), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[43], .mode = NO_TILING,
		.filter = WHITE, .overlay =	NULL};
		tmp.texture = &game->textures[59];
	materials[35] = tmp;
	tmp.texture = &game->textures[60];
	materials[36] = tmp;
	tmp.texture = &game->textures[61];
	materials[37] = tmp;
	// tmp.texture = &game->textures[54];
	// materials[30] = tmp;
	// tmp.texture = &game->textures[55];
	// materials[31] = tmp;
	// tmp.texture = &game->textures[56];
	// materials[32] = tmp;
	// tmp.texture = &game->textures[57];
	// materials[33] = tmp;
	// tmp.texture = &game->textures[58];
	// materials[34] = tmp;
	return (materials);
}

t_mat	*init_mat_5(t_mat *materials, t_game *game)
{
	t_mat tmp;

	tmp = (t_mat) {.pos = fvec2_new(0, 0),
		.sca = fvec2_new(f_from_int(2), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[43], .mode = NO_TILING,
		.filter = WHITE, .overlay =	NULL};
		tmp.texture = &game->textures[51];
	materials[27] = tmp;
	tmp.texture = &game->textures[52];
	materials[28] = tmp;
	tmp.texture = &game->textures[53];
	materials[29] = tmp;
	tmp.texture = &game->textures[54];
	materials[30] = tmp;
	tmp.texture = &game->textures[55];
	materials[31] = tmp;
	tmp.texture = &game->textures[56];
	materials[32] = tmp;
	tmp.texture = &game->textures[57];
	materials[33] = tmp;
	tmp.texture = &game->textures[58];
	materials[34] = tmp;
	return (materials);
}
