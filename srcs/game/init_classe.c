/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_classe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:38:48 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/20 18:38:49 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_entity	classe_1(t_array *multi_mats)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 1.30, .radius = 1, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 1.30, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = &multi_mats[0], .type = (t_entity_type)GUN_MARINE,
		.damage = 20});
	return (classe);
}

static t_entity	classe_2(t_array *multi_mats)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 0.40, .radius = 0.1, .rad_inter = 0,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 0.50, .radius = 0, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = &multi_mats[1], .type = (t_entity_type)KEY_CARD,
		.damage = 0});
	return (classe);
}

static t_entity classe_3(t_array *multi_mats)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 1.50, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 1.50, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = &multi_mats[2], .type = (t_entity_type)SMG_MARINE,
		.damage = 30});
	return (classe);
}

static t_entity classe_4(t_array *multi_mats)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 1.50, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 1.50, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = &multi_mats[3], .type = (t_entity_type)BLACK_MARINE,
		.damage = 50});
	return (classe);
}

static t_entity classe_5(t_array *multi_mats)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 1.50, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 1.50, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = &multi_mats[4], .type = (t_entity_type)RED_MARINE,
		.damage = 70});
	return (classe);
}

t_entity		*init_classe(t_game *game, t_array *multi_mats)
{
	t_entity	*classe;

	classe = (t_entity *)safe_malloc(5 * sizeof(t_entity), "init_classe");
	classe[0] = classe_1(multi_mats);
	classe[1] = classe_2(multi_mats);
	classe[2] = classe_3(multi_mats);
	classe[3] = classe_4(multi_mats);
	classe[4] = classe_5(multi_mats);
	game->nclasses = 5;
	return (classe);
}
