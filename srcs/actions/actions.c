/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:47:39 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/20 17:41:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <editor.h>

// void        spawn_entity(t_vec2 pos, size_t class_type, t_game game)
// {
//     // create_entity(pos, 0, game);
//     // assign_entity(t_assign_entity *state, t_game game)
// }

// void        kill_entity(int entity_id, t_game * game)
// {
//     /*
//     int i;

//     i = 0; 
//     while(game.entity[i] != entity_id)
//     {
//         i++;
//     }
//     delete_entity(i, game)

//     */
// }

// void        animate_sector(t_sector * move_sector)
// {
//     /*
//         if (is_animate == false)
//             if(move_sector.floor == move_sector.floor_a))
//                 add_animate(&move_sector.floor, move_sector.floor_b)
//             if(move_sector.ceiling == move_sector.ceiling_a)
//                 add_animate(&move_sector.ceiling, move_sector.ceiling_b)
//             if(move_sector.floor == move_sector.ceiling_b)
//                 add_animate(&move_sector.floor, move_sector.floor_a)
//             if(move_sector.ceiling == move_sector.floor_b)
//                 add_animate(&move_sector.ceiling, move_sector.ceiling_a)
//         }
//     */
// }

// void        health_down(t_entity * entity, int oof, t_game * game)
// {
//     // entity->life -= oof;
//     // if (entity->life <= 0)
//     //      kill_entity(entity->id, game);
// }

// void        health_up(t_entity * entity, int health)
// {
//     // entity->life += oof;
//     // if (entity->life > 100)
//         // entity->life = 100;
// }

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

// void    loading_anim(t_game game) // APPELER TOUTE LES (X A DETERMINER) SECONDES
// {
//     // t_list_anim    *current;
//     // while ((current = (t_list_anim *)lpnext(&game.anim)) != NULL)
//     // {
//     //     current->a_elem.moveTo = move_anim(current);
//     //     if (current->a_elem.moveTo == current->a_elem.moveGoal)
//     //         lpremove(&game.anim, (t_pelem *)current);
//     // }   
// }

// t_vec3      move_anim(t_list_anim c_anim)
// {
//     // if (c_anim.a_elem.moveTo < c_anim.a_elem.moveGoal)
//     // {
//     //     c_anim.a_elem.moveTo += 0.1;
//     // }
//     // else if (c_anim.a_elem.moveTo > c_anim.a_elem.moveGoal)
//     // {
//     //     c_anim.a_elem.moveTo -= 0.1;
//     // }
//     // return (c_anim.a_elem.moveTo);
// }

