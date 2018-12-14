/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo </var/spool/mail/hugo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:26:13 by hugo              #+#    #+#             */
/*   Updated: 2018/12/13 17:27:53 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_game	generate_map(void)
{
	t_game res;
	t_player player = (t_player) {
		(t_ph) {
			9.81,
			1.80,
			vec3_new(0, 0, 0),
			vec3_new(0, 0, 0),
			vec3_new(8, 8, 53),
			vec2_new(0, 0),
			vec2_new(2 * M_PI, M_PI / 2)
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
	apush(&points, &((t_wall){-1, 9, 0}));
	apush(&points, &((t_wall){-1, 0, 1}));
	apush(&points, &((t_wall){-1, 1, 2}));
	apush(&points, &((t_wall){-1, 2, 3}));
	apush(&points, &((t_wall){-1, 3, 4}));
	apush(&points, &((t_wall){-1, 4, 5}));
	apush(&points, &((t_wall){-1, 5, 6}));
	apush(&points, &((t_wall){-1, 6, 7}));
	apush(&points, &((t_wall){-1, 7, 8}));
	apush(&points, &((t_wall){0, 8, 9}));
	apush(&points, &((t_wall){0, 8, 9}));
	apush(&points, &((t_wall){-1, 9, 10}));
	apush(&points, &((t_wall){-1, 8, 11}));
	apush(&points, &((t_wall){1, 10, 11}));
	apush(&points, &((t_wall){1, 10, 11}));
	apush(&points, &((t_wall){-1, 11, 12}));
	apush(&points, &((t_wall){-1, 10, 13}));
	apush(&points, &((t_wall){2, 12, 13}));
	apush(&points, &((t_wall){2, 12, 13}));
	apush(&points, &((t_wall){-1, 13, 14}));
	apush(&points, &((t_wall){-1, 12, 15}));
	apush(&points, &((t_wall){3, 14, 15}));
	apush(&points, &((t_wall){3, 14, 15}));
	apush(&points, &((t_wall){-1, 15, 16}));
	apush(&points, &((t_wall){-1, 16, 17}));
	apush(&points, &((t_wall){-1, 17, 18}));
	apush(&points, &((t_wall){-1, 18, 19}));
	apush(&points, &((t_wall){-1, 19, 14}));

	t_array portals = anew(NULL, 4, sizeof(t_portal));
	apush(&points, &((t_portal){0, 1, 9, 0, 8, 9}));
	apush(&points, &((t_portal){1, 2, 3, 0, 10, 11}));
	apush(&points, &((t_portal){2, 3, 3, 0, 12, 13}));
	apush(&points, &((t_portal){3, 4, 3, 0, 14, 15}));

	t_array sectors = anew(NULL, 5, sizeof(t_sector));
	apush(&sectors, &((t_sector){0, 10, 0, 2.5}));
	apush(&sectors, &((t_sector){10, 4, 0.2, 2.7}));
	apush(&sectors, &((t_sector){14, 4, 0.4, 2.9}));
	apush(&sectors, &((t_sector){18, 4, 0.6, 3.1}));
	apush(&sectors, &((t_sector){22, 6, -30, 4.0}));

	res.player = player;
	res.sectors = sectors;
	res.walls = walls;
	res.portals = portals;
	res.points = points;
	return (res);
}
