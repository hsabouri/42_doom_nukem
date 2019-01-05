/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:19:28 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/05 12:21:36 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_event			init_events(void)
{
	t_event res;
	size_t	key;

	key = 0;
	res.left = 0;
	res.right = 0;
	res.x = 0;
	res.old_x = 0;
	res.y = 0;
	res.old_y = 0;
	while (key < N_KEY)
	{
		res.keys[key] = 0;
		key++;
	}
	res.quit = 0;
	return (res);
}

static t_event	mouse_event(t_event events, SDL_Event polled_event)
{
	if (polled_event.type == SDL_MOUSEMOTION)
	{
		events.old_x = events.x;
		events.old_y = events.y;
		events.x = polled_event.motion.x;
		events.y = polled_event.motion.y;
	}
	else if (polled_event.type == SDL_MOUSEBUTTONDOWN)
		events.left = 1;
	else if (polled_event.type == SDL_MOUSEBUTTONUP)
		events.left = 0;
	return (events);
}

t_event			capture_events(t_event events)
{
	SDL_Event	polled_event;

	SDL_CaptureMouse(SDL_TRUE);
	while (SDL_PollEvent(&polled_event))
	{
		if (polled_event.type == SDL_KEYDOWN)
			events.keys[polled_event.key.keysym.scancode] = 1;
		else if (polled_event.type == SDL_KEYUP)
			events.keys[polled_event.key.keysym.scancode] = 0;
		else if (polled_event.type == SDL_QUIT)
			events.quit = 1;
		events = mouse_event(events, polled_event);
	}
	SDL_CaptureMouse(SDL_FALSE);
	return (events);
}
