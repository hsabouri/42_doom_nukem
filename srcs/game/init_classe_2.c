/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_classe_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:22:25 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/30 18:22:27 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_entity classe_5(t_array *multi_mats)
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

t_entity	classe_6(t_array *multi_mats)
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
		}, .mat = &multi_mats[1], .type = (t_entity_type)BLUE_KEY_CARD,
		.damage = 0});
	return (classe);
}

t_entity	classe_7(t_array *multi_mats)
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
		}, .mat = &multi_mats[1], .type = (t_entity_type)RED_KEY_CARD,
		.damage = 0});
	return (classe);
}

t_entity	classe_8(t_array *multi_mats)
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
		}, .mat = &multi_mats[1], .type = (t_entity_type)PURPLE_KEY_CARD,
		.damage = 0});
	return (classe);
}