/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:30 by lbougero          #+#    #+#             */
/*   Updated: 2019/03/11 14:57:45 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>


void    no_trigger(t_trigger trigger)
{
    // (A and B -> OK)
}

void      see_trigger(t_trigger trigger)
{
    // if (A See B -> OK)
}

void      touch_trigger(t_trigger trigger)
{
    // if (colision A and B -> OK)
}

void      interact_trigger(t_trigger trigger)
{
    // if (A (PLAYER) interact with)
}

void    (* ft_trigger[4]) = {no_trigger, see_trigger,touch_trigger,interact_trigger};

t_game    choose_condition(t_game game, t_trigger trigger)
{
    t_game  n_game;

    n_game = game;

    // ft_trigger[trigger.condi](trigger);

    return (n_game);
}