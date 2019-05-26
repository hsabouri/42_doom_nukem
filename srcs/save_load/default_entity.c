/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_entity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 17:19:51 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/16 15:57:38 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_player	player_default(t_game game)
{
	return ((t_player) {
		(t_entity) {
			-1,
			(t_ph) {
				0.02,
				1.50,
				0.5,
				0,
				(t_vec3){6.5, 11, 0},
				(t_vec3){0, 0, 0},
				(t_vec3){1, 1, 1},
				0,
				0,
				0,
				0,
				0
			},
			(t_ph) {
				0.02,
				1.50,
				0.5,
				0,
				(t_vec3){6.5, 11, 0},
				(t_vec3){0, 0, 0},
				(t_vec3){1, 1, 1},
				0,
				0,
				0,
				0,
				0
			},
			&game.multi_mats[0],
			(t_entity_type)PLAYER,
			1
		},
		100,
		{0, 1},
		6,
		0,
		safe_anew(NULL, 1, sizeof(t_entity *), "generate_map")});
}

t_entity	entity_default(void)
{
	return ((t_entity) {
		1,
		(t_ph) {
			0.02,
			1.25,
			0.5,
			3,
			(t_vec3){7, 9, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		(t_ph) {
			0.02,
			1.25,
			0.5,
			3,
			(t_vec3){7, 9, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0
		},
		NULL,
		-1,
		0});
}

t_game	default_map(void)
{
	t_game game;

	game = generate_map();
	return (game);
}