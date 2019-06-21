/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 15:48:15 by fmerding          #+#    #+#             */
/*   Updated: 2019/06/21 15:48:17 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_event			reset_clicks(t_event events)
{
	size_t key;

	key = 0;
	while (key < N_BUTTON)
	{
		events.mouse_click[key] = 0;
		key++;
	}
	return (events);
}

t_event			init_events(void)
{
	t_event res;
	size_t	key;

	key = 0;
	res.x = 0;
	res.old_x = 0;
	res.y = 0;
	res.old_y = 0;
	res.any = 0;
	while (key < N_BUTTON)
	{
		res.mouse[key] = 0;
		key++;
	}
	res = reset_clicks(res);
	key = 0;
	while (key < N_KEY)
	{
		res.keys[key] = 0;
		key++;
	}
	res.quit = 0;
	return (res);
}
