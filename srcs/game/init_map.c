/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:06:02 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/18 16:54:46 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_vec2		*init_points(t_game *game)
{
	t_vec2 *points;

	points = (t_vec2 *)safe_malloc(sizeof(t_vec2) * 8, "generate_map");
	points[0] = ((t_vec2){5, 14});
	points[1] = ((t_vec2){8, 14});
	points[2] = ((t_vec2){10, 12});
	points[3] = ((t_vec2){10, 10});
	points[4] = ((t_vec2){8, 8});
	points[5] = ((t_vec2){5, 8});
	points[6] = ((t_vec2){3, 10});
	points[7] = ((t_vec2){3, 12});
	game->npoints = 8;
	return (points);
}

t_wall		*init_walls(t_game *game)
{
	t_wall *walls;

	walls = (t_wall *)safe_malloc(8 * sizeof(t_wall), "generate_map");
	walls[0] = ((t_wall){fvec2_new(0, 0), -1, 0, 1, &game->materials[3],
		(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[1] = ((t_wall){fvec2_new(0, 0), -1, 1, 2, &game->materials[3],
		(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[2] = ((t_wall){fvec2_new(0, 0), -1, 2, 3, &game->materials[3],
		(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[3] = ((t_wall){fvec2_new(0, 0), -1, 3, 4, &game->materials[0],
		(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[4] = ((t_wall){fvec2_new(0, 0), -1, 4, 5, &game->materials[0],
		(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[5] = ((t_wall){fvec2_new(0, 0), -1, 5, 6, &game->materials[0],
		(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[6] = ((t_wall){fvec2_new(0, 0), -1, 6, 7, &game->materials[0],
		(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	walls[7] = ((t_wall){fvec2_new(0, 0), -1, 7, 0, &game->materials[0],
		(t_vec2){0, 2.5}, (t_vec2){0, 2.5}});
	game->nwalls = 8;
	game->nuwalls = 0;
	return (walls);
}

t_sector	*init_sector(t_game *game)
{
	t_sector *sectors;

	sectors = (t_sector *)safe_malloc(1 * sizeof(t_sector), "generate_map");
	sectors[0] = ((t_sector){0, 8, 0, (t_vec3){0, 0, 0}, (t_vec3){0, 0, 2.50},
		(t_vec3){0, 0, 0}, (t_vec3){0, 0, 2.50},
		(t_color) {125, 125, 125, 255}, &game->materials[1],
			&game->materials[1], fvec2_new(0, 0), (t_vec2){0, 0}, 0});
	game->nsectors = 1;
	return (sectors);
}

t_entity	*init_entities(t_game *game)
{
	t_entity *entities;

	entities = (t_entity *)malloc(1 * sizeof(t_entity));
	entities[0] = game->classes[0];
	entities[0].id = 0;
	entities[0].physic.pos = (t_vec3){8, 12, 0};
	entities[0].spawn.pos = (t_vec3){8, 12, 0};
	game->nentities = 1;
	return (entities);
}
