/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:19:28 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/14 16:01:33 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_event		capture_events()
{
	SDL_Event	polled_event;
	t_event		new_table;

	while (SDL_PollEvent(&polled_event))
	{
		if (polled_event.type == SDL_KEYDOWN)
			new_table.keys[polled_event.key.keysym.scancode] = 1;
		else if (polled_event.type == SDL_KEYUP)
			new_table.keys[polled_event.key.keysym.scancode] = 0;
	}
	return (new_table);
}