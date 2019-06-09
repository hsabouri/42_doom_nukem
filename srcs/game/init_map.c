/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:06:02 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/09 17:52:54 by lbougero         ###   ########.fr       */
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
		(t_color) {125, 125, 125, 255}, &game->materials[1],
			&game->materials[1], fvec2_new(0, 0), (t_vec2){0, 0}, 0});
	game->nsectors = 1;
	return (sectors);
}

void	entities_event(t_entity	*entity, t_game *game)
{
	t_plist	g_e;
	t_game_event * first_e = (t_game_event *)malloc(sizeof(t_game_event));
	first_e = (t_game_event *)malloc(sizeof(t_game_event));
	g_e	= lpnew(NULL);
	if (entity->type == GUN_MARINE || entity->type == SMG_MARINE || entity->type == BLACK_MARINE || entity->type == RED_MARINE)
	{
		*first_e = (t_game_event){
		(t_pelem) {NULL, NULL},
		(t_trigger){
			game->player.my_entity, TRIGGER_SHOT, entity->id // Game event : list event wanted
			},
		(t_action){
			NULL ,&entity->id, ACTION_H_DOWN, 25
			}
		};
		printf("WRWQR %d\n", first_e->action.target->id);
		printf("LUUUL %d\n",entity->id);
		lppush(&g_e, (t_pelem *)first_e);
	}
	else if (entity->type == GREEN_KEY_CARD || entity->type == BLUE_KEY_CARD || entity->type == RED_KEY_CARD ||	entity->type == PURPLE_KEY_CARD) {
		*first_e = (t_game_event){
		(t_pelem) {NULL, NULL},
		(t_trigger){
			game->player.my_entity, TRIGGER_INTERACT, entity->id // Game event : list event wanted
			},
		(t_action){
			NULL ,&game->entities[entity->id], ACTION_ADD_INV, 0
			}
		};
		// printf("WRWQR %d\n", first_e->action.target->id;
		lppush(&g_e, (t_pelem *)first_e);
	}
	else if (entity->type == APPLE || entity->type == FISH || entity->type == MEAT || entity->type == MEDIPACK) {
		*first_e = (t_game_event){
		(t_pelem) {NULL, NULL},
		(t_trigger){
			game->player.my_entity, TRIGGER_INTERACT, entity->id // Game event : list event wanted
			},
		(t_action){
			NULL ,&game->entities[entity->id], ACTION_H_UP, 20
			}
		};
		lppush(&g_e, (t_pelem *)first_e);
	}

	entity->self_events = g_e;
}

t_entity		*init_entities(t_game *game)
{
	t_entity *entities;

	entities = (t_entity *)malloc(4 * sizeof(t_entity));
	entities[0] = game->classes[0];
	entities[0].id = 0;
	entities[0].life = 100;
	entities[0].physic.pos = (t_vec3){8, 12, 0};
	entities[0].spawn.pos = (t_vec3){8, 12, 0};
	entities_event(&entities[0], game);
	// entities[1] = game->classes[2];
	// entities[1].id = 1;
	// entities[1].life = 100;
	// entities[1].physic.pos = (t_vec3){5, 12, 0};
	// entities[1].spawn.pos = (t_vec3){5, 12, 0};
	// entities_event(&entities[1], game);
	
	// entities[2] = game->classes[3];
	// entities[2].id = 2;
	// entities[2].life = 100;
	// entities[2].physic.pos = (t_vec3){8, 10, 0};
	// entities[2].spawn.pos = (t_vec3){8, 10, 0};
	// entities_event(&entities[2], game);

	// entities[3] = game->classes[4];
	// entities[3].id = 3;
	// entities[3].life = 100;
	// entities[3].physic.pos = (t_vec3){5, 10, 0};
	// entities[3].spawn.pos = (t_vec3){5, 10, 0};
	// entities_event(&entities[3], game);
	game->nentities = 1;

	return (entities);
}
