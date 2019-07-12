/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_classe_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:57:58 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 09:58:25 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_entity	classe_1(t_entity_type type, t_array *mats, int data)
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

t_entity	classe_2(t_entity_type type, t_array *mats, t_vec3 v)
{
	t_entity	classe;

	classe = ((t_entity){
		.id = 0, .physic = (t_ph) {
			.gravity = 0.02, .height = v.z, .radius = v.y,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 1, .rad_inter = v.x
		}, .spawn = (t_ph) {
			.gravity = 0.02, .height = v.z, .radius = v.y, .rad_inter = v.x,
			.pos = (t_vec3){0, 0, 0}, .speed = (t_vec3){0, 0, 0},
			.speed_max = (t_vec3){0, 0, 0}, .look_h = 0, .look_v = 0,
			.sector_id = 0, .jump = 0, .fly = 1
		}, .mat = mats, .type = type,
		.data = 0, .life = 100});
	return (classe);
}

t_entity	classe_3(t_entity_type type, t_array *mats, int data)
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
	if (type == RACLURE)
		classe.life = 800;
	return (classe);
}

t_entity	classe_4(t_entity_type type, t_array *mats, int data)
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
