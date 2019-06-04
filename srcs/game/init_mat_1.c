/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mat_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:51:39 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/31 15:26:34 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_mat	*init_mat_7(t_mat *materials, t_game *game)
{
	t_mat tmp;

	tmp = (t_mat) {.pos = fvec2_new(0, 0),
		.sca = fvec2_new(f_from_int(1), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[67], .mode = NO_TILING,
		.filter = WHITE, .overlay =	NULL};
	materials[43] = tmp;
	tmp.texture = &game->textures[68];
	materials[44] = tmp;
	tmp.sca.u = f_from_float(1.5);
	tmp.texture = &game->textures[69];
	materials[45] = tmp;
	return (materials);
}

t_mat	*init_mat_6(t_mat *materials, t_game *game)
{
	t_mat tmp;

	tmp = (t_mat) {.pos = fvec2_new(0, 0),
		.sca = fvec2_new(f_from_float(1.5), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[59], .mode = NO_TILING,
		.filter = WHITE, .overlay =	NULL};
	materials[35] = tmp;
	tmp.texture = &game->textures[60];
	materials[36] = tmp;
	tmp.texture = &game->textures[61];
	materials[37] = tmp;
	tmp.texture = &game->textures[65];
	materials[41] = tmp;
	tmp.sca.u = f_from_int(3);
	tmp.texture = &game->textures[62];
	materials[38] = tmp;
	tmp.texture = &game->textures[63];
	materials[39] = tmp;
	tmp.texture = &game->textures[64];
	materials[40] = tmp;
	tmp.sca.u = f_from_int(1);
	tmp.texture = &game->textures[66];
	materials[42] = tmp;
	return (materials);
}

t_mat	*init_mat_5(t_mat *materials, t_game *game)
{
	t_mat tmp;

	tmp = (t_mat) {.pos = fvec2_new(0, 0),
		.sca = fvec2_new(f_from_float(1.5), f_from_int(1)),
		.color = NO_COLOR, .texture = &game->textures[51], .mode = NO_TILING,
		.filter = WHITE, .overlay =	NULL};
	materials[27] = tmp;
	tmp.texture = &game->textures[52];
	materials[28] = tmp;
	tmp.texture = &game->textures[53];
	materials[29] = tmp;
	tmp.sca.u = f_from_float(2.5);
	tmp.texture = &game->textures[54];
	materials[30] = tmp;
	tmp.sca.u = f_from_float(1.5);
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
