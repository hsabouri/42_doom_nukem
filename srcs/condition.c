/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:30 by lbougero          #+#    #+#             */
/*   Updated: 2019/03/11 15:05:07 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>


int    no_trigger(t_trigger trigger)
{
    // (A and B -> OK)
}

int      see_trigger(t_trigger trigger)
{
    // if (A See B -> OK)
}

int      touch_trigger(t_trigger trigger)
{
    if (colision A and B -> OK)
}

int      interact_trigger(t_trigger trigger)
{
    // if (A (PLAYER) interact with)
}

int      sector_trigger(t_trigger trigger)
{
    // Player / entitie is in a sector
}

int    (* ft_trigger[4]) = {no_trigger, see_trigger,touch_trigger,interact_trigger};

t_game    check_conditions(t_game game, t_game_event *trigger_tab)
{
    t_game  n_game;

    n_game = game;

    // while () {
        if (ft_trigger[trigger_tab[0].trigger.condi](trigger_tab[0].trigger) == 1);
        {
            //trigger_tab[0].trigger.action
        }
    //}

    return (n_game);
}