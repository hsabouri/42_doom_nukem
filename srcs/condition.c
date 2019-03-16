/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:30 by lbougero          #+#    #+#             */
/*   Updated: 2019/03/11 19:01:41 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

// TEST // SET entities to 0

t_game ft_reset_log(t_game game)
{
    t_game n_game;
    n_game = game;

    t_entity Z_E = ((t_entity){
		-2,
		(t_ph) {
			0,
			0,
			0,
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			0,
			0,
			0,
			0,
			0
		},
		(t_ph) {
			0,
			0,
			0,
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			(t_vec3){0, 0, 0},
			0,
			0,
			0,
			0,
			0
		},
		0,
		0
		});

        t_trigger trig_Z = ((t_trigger){Z_E, TRIGGER_NO, Z_E});

        int i = 0;
        while(i < 3)
        {
            n_game.log[i] = trig_Z;
            i++;
        }
    return(n_game);
}

//////////


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
      if (trigger.condi == TRIGGER_TOUCH && trigger.e_actif.id == c_log.e_actif.id && trigger.e_passif.id == c_log.e_passif.id)
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

int    (* ft_trigger[4])(t_trigger trigger, t_trigger c_log) = {no_trigger, see_trigger,touch_trigger,interact_trigger};

t_game    check_conditions(t_game game)
{
    t_game  n_game;

    n_game = game;
    int i = 0;
    int j = 0;

    while (i < game.nwaiting_events) {
        while (j < game.nlog) {
            if (ft_trigger[game.waiting_events[i].trigger.condi] (game.waiting_events[i].trigger, n_game.log[j]) == 1)
            {
                ft_putendl("HELLO !!!"); // Action trigger Zone
            }
            j++;
        }
        j = 0;
        i++;
    }

    return (n_game);
}