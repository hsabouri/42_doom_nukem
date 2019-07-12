/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_classe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:38:48 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/12 10:25:36 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_entity	*init_classe_2(t_entity *classe, t_array *m_mats)
{
	classe[17] = classe_2(OPEN_RED, &m_mats[17], (t_vec3){0.5, 0.4, 0.4});
	classe[18] = classe_2(OPEN_BLUE, &m_mats[18], (t_vec3){0.5, 0.4, 0.4});
	classe[19] = classe_2(OPEN_GREEN, &m_mats[19], (t_vec3){0.5, 0.4, 0.4});
	classe[20] = classe_2(OPEN_PURPLE, &m_mats[20], (t_vec3){0.5, 0.4, 0.4});
	classe[21] = classe_2(LAMP, &m_mats[21], (t_vec3){0, 0.4, 1.5});
	classe[22] = classe_2(CEIL_LAMP, &m_mats[22], (t_vec3){0, 0.4, 0.4});
	classe[23] = classe_2(PLANT_1, &m_mats[23], (t_vec3){0, 0.4, 1});
	classe[24] = classe_2(PLANT_2, &m_mats[24], (t_vec3){0, 0.4, 0.5});
	classe[25] = classe_2(PLANT_3, &m_mats[25], (t_vec3){0, 0.4, 0.9});
	classe[26] = classe_2(PLANT_4, &m_mats[26], (t_vec3){0, 0.4, 0.4});
	classe[27] = classe_2(TRASH_1, &m_mats[27], (t_vec3){0, 0.4, 0.5});
	classe[28] = classe_2(TRASH_2, &m_mats[28], (t_vec3){0, 0.4, 0.8});
	classe[29] = classe_2(GUN, &m_mats[29], (t_vec3){0, 0.4, 0.8});
	classe[30] = classe_2(SMG, &m_mats[30], (t_vec3){0, 0.4, 0.8});
	classe[31] = classe_2(SHOTGUN, &m_mats[31], (t_vec3){0, 0.4, 0.8});
	classe[32] = classe_2(REVOLVER, &m_mats[32], (t_vec3){0, 0.4, 0.8});
	classe[33] = classe_2(NYAN_GUN, &m_mats[33], (t_vec3){0, 0.8, 0.8});
	return (classe);
}

t_entity		*init_classe(t_game *game, t_array *m_mats)
{
	t_entity	*classe;

	game->nclasses = 34;
	classe = (t_entity *)safe_malloc(game->nclasses * sizeof(t_entity),
		"init_classe");
	classe[0] = classe_1(GUN_MARINE, &m_mats[0], 15);
	classe[1] = classe_2(GREEN_KEY_CARD, &m_mats[1], (t_vec3){1, 0.4, 0.4});
	classe[2] = classe_1(SMG_MARINE, &m_mats[2], 30);
	classe[3] = classe_3(RACLURE, &m_mats[3], 30);
	classe[4] = classe_3(RED_MARINE, &m_mats[4], 30);
	classe[5] = classe_2(BLUE_KEY_CARD, &m_mats[5], (t_vec3){1, 0.4, 0.4});
	classe[6] = classe_2(RED_KEY_CARD, &m_mats[6], (t_vec3){1, 0.4, 0.4});
	classe[7] = classe_2(PURPLE_KEY_CARD, &m_mats[7], (t_vec3){1, 0.4, 0.4});
	classe[8] = classe_4(APPLE, &m_mats[8], -20);
	classe[9] = classe_4(FISH, &m_mats[9], -50);
	classe[10] = classe_4(MEAT, &m_mats[10], -70);
	classe[11] = classe_4(MEDIPACK, &m_mats[11], -100);
	classe[12] = classe_2(AMMO, &m_mats[12], (t_vec3){3, 0.4, 0.4});
	classe[13] = classe_2(CLOSE_RED, &m_mats[13], (t_vec3){0.5, 0.4, 0.4});
	classe[14] = classe_2(CLOSE_BLUE, &m_mats[14], (t_vec3){0.5, 0.4, 0.4});
	classe[15] = classe_2(CLOSE_GREEN, &m_mats[15], (t_vec3){0.5, 0.4, 0.4});
	classe[16] = classe_2(CLOSE_PURPLE, &m_mats[16], (t_vec3){0.5, 0.4, 0.4});
	return (init_classe_2(classe, m_mats));
}
