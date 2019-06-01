/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:47:39 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/30 18:51:18 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <editor.h>

//
typedef int (*ft_actions)(t_vec2 pos, t_entity *target, t_game *game); // Wat ?

t_env     init_actions(void)
{
	t_env env;
	
	ft_actions *actions = malloc(sizeof(ft_trigger) * 5);
	actions[0] = spawn_entity; 
	actions[1] = kill_entity;
	actions[2] = health_down;
	actions[3] = health_up;
    actions[4] = add_inventory;

	// env.actions = actions;
	return (env);
}

void        spawn_entity(t_vec2 pos, t_entity *target, t_game *game) // action
{
    // create_entity(pos, 0, game);
    // assign_entity(t_assign_entity *state, t_game game)
}

void        kill_entity(t_vec2 pos, t_entity *target, t_game *game) // action
{
    //entity
    
    int i;

    i = 0; 
    while(target[i] != target.id)
    {
        i++;
    }
    delete_entity(i, game)
}

void        health_down(t_vec2 pos,t_entity *target, t_game *game) // action
{
    target->life = 1;
    if (target->life <= 0)
         kill_entity(target);
}

void        health_up(t_vec2 pos, t_entity *target, t_game *game) // action
{
    target->life = 1;
    if (target->life > 100)
        target->life = 100;
}

void        add_inventory(t_vec2 pos, t_entity *target, t_game *game) 
{
    lppush(&game->player.inventory, target);
}

void        remove_inventory(t_vec2 pos, t_entity *target, t_game *game)
{
    lpremove(&game->player.inventory, target);
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