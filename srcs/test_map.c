/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:26:13 by hugo              #+#    #+#             */
/*   Updated: 2018/12/21 13:39:25 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	generate_map(t_game game)
{
	t_player player = (t_player) {
		(t_ph) {
			9.81,
			1.80,
			(t_vec3){10, 10, 0, 1},
			(t_vec3){0, 0, 0, 1},
			(t_vec3){8, 8, 53, 1},
			(t_vec2){0, 0, 1},
			(t_vec2){2 * M_PI, M_PI / 2, 1}
		}
	};

	t_array points = anew(NULL, 19, sizeof(t_vec2));
	apush(&points, &((t_vec2){7, 6, 1}));
	apush(&points, &((t_vec2){8, 7, 1}));
	apush(&points, &((t_vec2){8, 11, 1}));
	apush(&points, &((t_vec2){5, 12, 1}));
	apush(&points, &((t_vec2){4, 12, 1}));
	apush(&points, &((t_vec2){1, 11, 1}));
	apush(&points, &((t_vec2){1, 7, 1}));
	apush(&points, &((t_vec2){2, 6, 1}));
	apush(&points, &((t_vec2){4, 6, 1}));
	apush(&points, &((t_vec2){5, 6, 1}));
	apush(&points, &((t_vec2){5, 4.5, 1}));
	apush(&points, &((t_vec2){4, 4, 1}));
	apush(&points, &((t_vec2){6, 2, 1}));
	apush(&points, &((t_vec2){6.5, 3, 1}));
	apush(&points, &((t_vec2){7, 3, 1}));
	apush(&points, &((t_vec2){7, 2, 1}));
	apush(&points, &((t_vec2){8, 0, 1}));
	apush(&points, &((t_vec2){9, 0, 1}));
	apush(&points, &((t_vec2){9, 5, 1}));
	apush(&points, &((t_vec2){8, 5, 1}));

	t_array walls = anew(NULL, 38, sizeof(t_wall));
	apush(&walls, &((t_wall){-1, 9, 0}));
	apush(&walls, &((t_wall){-1, 0, 1}));
	apush(&walls, &((t_wall){-1, 1, 2}));
	apush(&walls, &((t_wall){-1, 2, 3}));
	apush(&walls, &((t_wall){-1, 3, 4}));
	apush(&walls, &((t_wall){-1, 4, 5}));
	apush(&walls, &((t_wall){-1, 5, 6}));
	apush(&walls, &((t_wall){-1, 6, 7}));
	apush(&walls, &((t_wall){-1, 7, 8}));
	apush(&walls, &((t_wall){0, 8, 9}));
	apush(&walls, &((t_wall){0, 8, 9}));
	apush(&walls, &((t_wall){-1, 9, 10}));
	apush(&walls, &((t_wall){-1, 8, 11}));
	apush(&walls, &((t_wall){1, 10, 11}));
	apush(&walls, &((t_wall){1, 10, 11}));
	apush(&walls, &((t_wall){-1, 11, 12}));
	apush(&walls, &((t_wall){-1, 10, 13}));
	apush(&walls, &((t_wall){2, 12, 13}));
	apush(&walls, &((t_wall){2, 12, 13}));
	apush(&walls, &((t_wall){-1, 13, 14}));
	apush(&walls, &((t_wall){-1, 12, 15}));
	apush(&walls, &((t_wall){3, 14, 15}));
	apush(&walls, &((t_wall){3, 14, 15}));
	apush(&walls, &((t_wall){-1, 15, 16}));
	apush(&walls, &((t_wall){-1, 16, 17}));
	apush(&walls, &((t_wall){-1, 17, 18}));
	apush(&walls, &((t_wall){-1, 18, 19}));
	apush(&walls, &((t_wall){-1, 19, 14}));

	t_array portals = anew(NULL, 4, sizeof(t_portal));
	apush(&portals, &((t_portal){0, 1, 9, 0, 8, 9}));
	apush(&portals, &((t_portal){1, 2, 3, 0, 10, 11}));
	apush(&portals, &((t_portal){2, 3, 3, 0, 12, 13}));
	apush(&portals, &((t_portal){3, 4, 3, 0, 14, 15}));

	t_array sectors = anew(NULL, 5, sizeof(t_sector));
	apush(&sectors, &((t_sector){0, 10, 0, 2.5}));
	apush(&sectors, &((t_sector){10, 4, 0.2, 2.7}));
	apush(&sectors, &((t_sector){14, 4, 0.4, 2.9}));
	apush(&sectors, &((t_sector){18, 4, 0.6, 3.1}));
	apush(&sectors, &((t_sector){22, 6, -30, 4.0}));

	game.player = player;
	game.sectors = sectors;
	game.walls = walls;
	game.portals = portals;
	game.points = points;
	return (game);
}
