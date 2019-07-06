/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_classe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:38:48 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/22 20:00:46 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_entity	classe_1(t_entity_type type, t_array *mats, int data)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 1.30, .radius = 0.8, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 1.30, .radius = 0.8, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = mats, .type = type,
		.data = data, .life = 100});
	return (classe);
}

static t_entity	classe_2(t_entity_type type, t_array *mats, float rad_inter,
float rad, float height)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = height, .radius = rad,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 1, .rad_inter = rad_inter
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 0.40, .radius = rad, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 1
		}, .mat = mats, .type = type,
		.data = 0, .life = 100});
	return (classe);
}

static t_entity	classe_3(t_entity_type type, t_array *mats, int data)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 1.30, .radius = 0.6, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 1.30, .radius = 0.6, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = mats, .type = type,
		.data = data, .life = 200});
	return (classe);
}

static t_entity	classe_4(t_entity_type type, t_array *mats, int data)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 0.40, .radius = 0.3, .rad_inter = 0,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 1
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 0.40, .radius = 0.3, .rad_inter = 0,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 1
		}, .mat = mats, .type = type,
		.data = data, .life = 100});
	return (classe);
}

t_entity		*init_classe(t_game *game, t_array *multi_mats)
{
	t_entity	*classe;

	game->nclasses = 35;
	classe = (t_entity *)safe_malloc(game->nclasses * sizeof(t_entity),
		"init_classe");
	classe[0] = classe_1(GUN_MARINE, &multi_mats[0], 15);
	classe[1] = classe_2(GREEN_KEY_CARD, &multi_mats[1], 0, 0.4, 0.4);
	classe[2] = classe_1(SMG_MARINE, &multi_mats[2], 30);
	classe[3] = classe_3(BLACK_MARINE, &multi_mats[3], 50);
	classe[4] = classe_3(RED_MARINE, &multi_mats[4], 70);
	classe[5] = classe_2(BLUE_KEY_CARD, &multi_mats[5], 0, 0.4, 0.4);
	classe[6] = classe_2(RED_KEY_CARD, &multi_mats[6], 0, 0.4, 0.4);
	classe[7] = classe_2(PURPLE_KEY_CARD, &multi_mats[7], 0, 0.4, 0.4);
	classe[8] = classe_4(APPLE, &multi_mats[8], -20);
	classe[9] = classe_4(FISH, &multi_mats[9], -50);
	classe[10] = classe_4(MEAT, &multi_mats[10], -70);
	classe[11] = classe_4(MEDIPACK, &multi_mats[11], -100);
	classe[12] = classe_2(AMMO, &multi_mats[12], 3, 0.4, 0.4);
	classe[13] = classe_2(CLOSE_RED, &multi_mats[13], 3, 0.4, 0.4);
	classe[14] = classe_2(CLOSE_BLUE, &multi_mats[14], 3, 0.4, 0.4);
	classe[15] = classe_2(CLOSE_GREEN, &multi_mats[15], 3, 0.4, 0.4);
	classe[16] = classe_2(CLOSE_PURPLE, &multi_mats[16], 3, 0.4, 0.4);
	classe[17] = classe_2(OPEN_RED, &multi_mats[17], 3, 0.4, 0.4);
	classe[18] = classe_2(OPEN_BLUE, &multi_mats[18], 3, 0.4, 0.4);
	classe[19] = classe_2(OPEN_GREEN, &multi_mats[19], 3, 0.4, 0.4);
	classe[20] = classe_2(OPEN_PURPLE, &multi_mats[20], 3, 0.4, 0.4);
	classe[21] = classe_2(LAMP, &multi_mats[21], 0, 0.4, 1.5);
	classe[22] = classe_2(CEIL_LAMP, &multi_mats[22], 0, 0.4, 0.4);
	classe[23] = classe_2(PLANT_1, &multi_mats[23], 0, 0.4, 1);
	classe[24] = classe_2(PLANT_2, &multi_mats[24], 0, 0.4, 0.5);
	classe[25] = classe_2(PLANT_3, &multi_mats[25], 0, 0.4, 0.9);
	classe[26] = classe_2(PLANT_4, &multi_mats[26], 0, 0.4, 0.4);
	classe[27] = classe_2(TRASH_1, &multi_mats[27], 0, 0.4, 0.5);
	classe[28] = classe_2(TRASH_2, &multi_mats[28], 0, 0.4, 0.8);
	classe[29] = classe_2(GUN, &multi_mats[29], 0, 0.4, 0.8);
	classe[30] = classe_2(SMG, &multi_mats[30], 0, 0.4, 0.8);
	classe[31] = classe_2(SHOTGUN, &multi_mats[31], 0, 0.4, 0.8);
	classe[32] = classe_2(REVOLVER, &multi_mats[32], 0, 0.4, 0.8);
	classe[33] = classe_2(NYAN_GUN, &multi_mats[33], 0, 0.8, 0.8);
	classe[34] = classe_2(WC, &multi_mats[34], 0, 0.4, 0.8);
	return (classe);
}
