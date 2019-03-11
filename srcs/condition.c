/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:30 by lbougero          #+#    #+#             */
/*   Updated: 2019/03/11 17:43:52 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>


int    no_trigger(t_trigger trigger, t_trigger c_log)
{
    // (A and B -> OK)
}

int      see_trigger(t_trigger trigger, t_trigger c_log)
{
    // if (A See B -> OK)
}

int      touch_trigger(t_trigger trigger, t_trigger c_log)
{
        if (trigger.condi == TRIGGER_TOUCH && trigger.e_actif == c_log.trigger.e_actif && trigger.e_passif == c_log[0].trigger.e_passif)
            return 1;
        return 0;
}

int      interact_trigger(t_trigger trigger, t_trigger c_log)
{
    // if (A (PLAYER) interact with)
}

int      sector_trigger(t_trigger trigger, t_trigger c_log)
{
    // Player / entitie is in a sector
}

int    (* ft_trigger[4]) = {no_trigger, see_trigger,touch_trigger,interact_trigger};

t_game    check_conditions(t_game game, t_game_event *trigger_tab)
{
    t_game  n_game;

    n_game = game;

    // while (GAME_EVENT 0 -> len) {
    // you check , it seems OK, but change the player type
        if (ft_trigger[trigger_tab[0].trigger.condi](trigger_tab[0].trigger, n_game.log[0]) == 1);
        {
            if (n_game.entities[3] == NULL) {
                n_game.entities[3] = ((t_entity){
            (t_ph) {
                0.02,
                1.50,
                0.5,
                (t_vec3){5, 8.5, 0},
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
                (t_vec3){7, 9.5, 0},
                (t_vec3){0, 0, 0},
                (t_vec3){1, 1, 1},
                0,
                0,
                0,
                0,
                0
            },
            game.materials[3],
            1
            });
            //trigger_tab[0].trigger.action
            }
        }
    //}

    return (n_game);
}