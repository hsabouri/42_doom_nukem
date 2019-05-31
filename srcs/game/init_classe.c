/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_classe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:38:48 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/31 15:22:06 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_entity	classe_1(t_entity_type type, t_array *mats, int damage)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 1.30, .radius = 0.8, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 1.30, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = mats, .type = type,
		.damage = damage});
	return (classe);
}

static t_entity	classe_2(t_entity_type type, t_array *mats)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 0.40, .radius = 0.4, .rad_inter = 0,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 0.50, .radius = 0, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = mats, .type = type,
		.damage = 0});
	return (classe);
}

static t_entity classe_3(t_entity_type type, t_array *mats, int damage)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 1.30, .radius = 0.6, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 1.50, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = mats, .type = type,
		.damage = damage});
	return (classe);
}

static t_entity	classe_4(t_entity_type type, t_array *mats, int damage)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 0.40, .radius = 0.3, .rad_inter = 0,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 0.50, .radius = 0, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = mats, .type = type,
		.damage = damage});
	return (classe);
}

t_entity		*init_classe(t_game *game, t_array *multi_mats)
{
	t_entity	*classe;

	classe = (t_entity *)safe_malloc(13 * sizeof(t_entity), "init_classe");
	classe[0] = classe_1(GUN_MARINE, &multi_mats[0], 15);
	classe[1] = classe_2(GREEN_KEY_CARD, &multi_mats[1]);
	classe[2] = classe_1(SMG_MARINE, &multi_mats[2], 30);
	classe[3] = classe_3(BLACK_MARINE, &multi_mats[3], 50);
	classe[4] = classe_3(RED_MARINE, &multi_mats[4], 70);
	classe[5] = classe_2(BLUE_KEY_CARD, &multi_mats[5]);
	classe[6] = classe_2(RED_KEY_CARD, &multi_mats[6]);
	classe[7] = classe_2(PURPLE_KEY_CARD, &multi_mats[7]);
	classe[8] = classe_4(APPLE, &multi_mats[8], -20);
	classe[9] = classe_4(FISH, &multi_mats[9], -50);
	classe[10] = classe_4(MEAT, &multi_mats[10], -70);
	classe[11] = classe_4(MEDIPACK, &multi_mats[11], -100);
	classe[12] = classe_2(AMMO, &multi_mats[12]);
	game->nclasses = 13;
	return (classe);
}
