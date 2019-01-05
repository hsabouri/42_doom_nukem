/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 11:42:34 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/05 12:13:52 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_ph			update_mouse(t_event *events, t_ph player_physic)
{
	const float		pi = 3.141592;
	const float		eps = 0.001;

	player_physic.look.u += LOOK_SPEED * (events->x - events->old_x);
	player_physic.look.v += LOOK_SPEED * (events->y - events->old_y);
	printf("%d - %d\n", events->x, events->y);
	events->old_x = events->x;
	events->old_y = events->y;
	return (player_physic);
}
