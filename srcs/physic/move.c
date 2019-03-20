/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 11:42:34 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/20 14:36:44 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_ph			update_mouse(t_event *events, t_ph player_physic)
{
	player_physic.look_h -= LOOK_SPEED * (events->x - events->old_x);
	player_physic.look_v -=\
		f_from_float(LOOK_SPEED) * 2 * (events->y - events->old_y);
	if (player_physic.look_v >= f_from_int(10))
		player_physic.look_v = f_from_int(10);
	if (player_physic.look_v <= f_from_int(-10))
		player_physic.look_v = f_from_int(-10);
	events->old_x = events->x;
	events->old_y = events->y;
	return (player_physic);
}
