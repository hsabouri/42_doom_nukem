/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:47:39 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/17 15:15:35 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <editor.h>

void        spawn_entity(t_vec2 pos, t_entity *target, t_game *game, int num)
{
    (void)num;
    create_entity(pos, target->type, *game);
    // assign_entity(t_assign_entity *state, t_game game)
}

void        kill_entity(t_vec2 pos, t_entity *target, t_game *game, int num)
{
    int i;

    i = 0;
    while(game->entities[i].id != target->id)
        i++;
    printf("\x1b[31mentity n'%d (u_id: %d) : DIE\x1b[0m\n", i, game->entities[i].id);
    *game = delete_entity(game->entities[i].id, *game);
    (void)pos;
    (void)num;
}

void        health_down(t_vec2 pos, t_entity *target, t_game *game, int num)
{
    printf("entity (u_id: %d) : HEALTH_DOWN (%f", target->id, target->life);
    target->life -= num;
    printf(" -> %f)\n", target->life);
    if (target->life <= 0)
	{
		printf("	");
		kill_entity(pos, target, game, num);
	}
    (void)pos;
    (void)game;
}

void        health_up(t_vec2 pos, t_entity *target, t_game *game, int num)
{
    printf("entity (u_id: %d) : HEALTH_UP (%f", target->id, target->life);
    target->life += num;
    if (target->life > 100)
        target->life = 100;
    printf(" -> %f)\n", target->life);
    (void)pos;
    (void)target;
    (void)game;
}

void        add_inventory(t_vec2 pos, t_entity *target, t_game *game, int num)
{
	apush(&game->player.inventory, &target);
    printf("entity (u_id: %d) : ADD TO PLAYER INVENTORY", target->id);
	(void)num;
	(void)pos;
}

// void add_animate(t_vec3 * moveTo, t_vec3 moveGoal, t_game *game)
// {
//  /*
//     t_list_anim * new_element = (t_list_anim *)malloc(sizeof(t_list_anim));
//     *new_element = (t_list_anim) {
//         (t_pelem){NULL,NULL},
//         (t_anim_element){&moveTo,moveGoal}
//         };
//     }
//     if (game->anim.len == 0)
//     {
//         t_plist	anim = lpnew((t_pelem *)new_element);
//         game->anim = anim;
//     } else {
//         lppush(game->anim, (t_pelem *)new_element;
//     }
//  */
// }

/*
ADD INFINITY GAME EVENT
    create_entity
*/


void     init_actions(t_env *env)
{
	ft_actions *actions = malloc(sizeof(ft_trigger) * 5);
	actions[1] = kill_entity;
	actions[2] = health_down;
	actions[3] = health_up;
    actions[4] = add_inventory;

	env->actions = actions;
}
