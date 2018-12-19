/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:19:28 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/17 16:48:44 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_event			init_events(void)
{
	t_event res;
	size_t	key;

	key = 0;
	while (key < N_KEY)
	{
		res.keys[key] = 0;
		key++;
	}
	res.quit = 0;
	return (res);
}

t_event			capture_events(t_event events)
{
	SDL_Event	polled_event;

	while (SDL_PollEvent(&polled_event))
	{
		if (polled_event.type == SDL_KEYDOWN)
			events.keys[polled_event.key.keysym.scancode] = 1;
		else if (polled_event.type == SDL_KEYUP)
			events.keys[polled_event.key.keysym.scancode] = 0;
		else if (polled_event.type == SDL_QUIT)
			events.quit = 1;
	}
	return (events);
}
