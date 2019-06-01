/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_entity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 17:19:51 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/01 11:47:53 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_player	player_default(t_game game)
{
	t_player	player;

	player = (t_player) {
			(t_entity) {
			-1,
			(t_ph) {.gravity = 0.02, .height = 1.50, .radius = 0.5,
				.pos = (t_vec3){6.5, 11, 0}, .speed_max = (t_vec3){1, 1, 1},
			},
			(t_ph) {.gravity = 0.02, .height = 1.50, .radius = 0.5,
				.pos = (t_vec3){6.5, 11, 0}, .speed_max = (t_vec3){1, 1, 1},
			},
			&game.multi_mats[0],
			(t_entity_type)PLAYER,
			0
		},
		100,
		{0, 1},
		6,
		0,
		lpnew(NULL);
}

t_entity	entity_default(void)
{
	t_entity entity;

	entity = ((t_entity) {
		1,
		(t_ph) {.gravity = 0.02, .height = 1.25, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){7, 9, 0}, .speed_max = (t_vec3){1, 1, 1},
		},
		(t_ph) {.gravity = 0.02, .height = 1.25, .radius = 0.5, .rad_inter = 3,
			.pos = (t_vec3){7, 9, 0}, .speed_max = (t_vec3){1, 1, 1},
		},
		NULL,
		-1,
		0});
	return (entity);
}

t_game		default_map(void)
{
	t_game game;

	game = generate_map();
	return (game);
}
