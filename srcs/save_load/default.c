/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 17:19:51 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/16 15:57:38 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_player	player_default(void)
{
	t_array inventory = safe_anew(NULL, 1, sizeof(t_entity), "loader");

	return ((t_player) {
		(t_entity) {
			-1,
			(t_ph) {
				0.02,
				1.50,
				0.5,
				0,
				(t_vec3){2, 10, 0},
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
				(t_vec3){2, 10, 0},
				(t_vec3){0, 0, 0},
				(t_vec3){1, 1, 1},
				0,
				0,
				0,
				0,
				0
			},
			NULL,
			"player",
			1
		},
		90,
		{0, 1},
		6,
		0,
		inventory
	});
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
		"null",
		0});
}

t_game	default_map(void)
{
	t_game game;

	game = generate_map();
	return (game);
}
