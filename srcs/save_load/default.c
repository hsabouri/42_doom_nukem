/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 17:19:51 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/13 12:20:13 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_player	player_default(void)
{
	t_array inventory = safe_anew(NULL, 1, sizeof(t_entity), "loader");

	t_player player = (t_player) {
		(t_ph) {
			0.05,
			1.25,
			0,
			0,
			(t_vec3){7, 9, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0,
		},
		(t_ph) {
			0.05,
			1.25,
			0,
			0,
			(t_vec3){7, 9, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){1, 1, 1},
			0,
			0,
			0,
			0,
			0,
		},
		100,
		{0, 1},
		6,
		0,
		inventory,
	};
	return (player);
}

t_entity	entity_default(void)
{
	return ((t_entity) {
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
	safe_anew(NULL, 1, sizeof(t_img), "components"),
	0});
}

t_game	default_map(void)
{
	t_game game;

	game = generate_map();
	return (game);
}
