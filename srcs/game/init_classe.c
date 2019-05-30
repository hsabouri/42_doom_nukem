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
			.gravity = 0.02, .height = 1.50, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = 1.50, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){1, 1, 1}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 0
		}, .mat = &multi_mats[0], .type = (t_entity_type)GUN_MARINE,
		.damage = 10});
	return (classe);
}

static t_entity	classe_2(t_array *multi_mats)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = 0.50, .radius = 0, .rad_inter = 3,
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

t_entity		*init_classe(t_game *game, t_array *multi_mats)
{
	t_entity	*classe;

	classe = (t_entity *)safe_malloc(2 * sizeof(t_entity), "init_classe");
	classe[0] = classe_1(multi_mats);
	classe[1] = classe_2(multi_mats);
	game->nclasses = 2;
	return (classe);
}
