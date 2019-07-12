/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:19:28 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/23 14:31:57 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_event	mouse_event(t_event events, SDL_Event polled_event, int *any)
{
	if (polled_event.type == SDL_MOUSEMOTION)
	{
		events.old_x = events.x;
		events.old_y = events.y;
		events.x = polled_event.motion.x;
		events.y = polled_event.motion.y;
	}
	else if (polled_event.type == SDL_MOUSEBUTTONDOWN)
	{
		(*any)++;
		events.mouse[polled_event.button.button] = 1;
		events.mouse_click[polled_event.button.button] = 1;
	}
	else if (polled_event.type == SDL_MOUSEBUTTONUP)
	{
		(*any)--;
		events.mouse[polled_event.button.button] = 0;
	}
	else if (polled_event.type == SDL_MOUSEWHEEL)
		events.wheel = (polled_event.wheel.y > 0) ? 1 : -1;
	return (events);
}

static void		keyactions_2(int scancode, t_env *env)
{
	if (scancode == SDL_SCANCODE_TAB)
	{
		env->game.player.equiped = (env->game.player.equiped == 0) ? 1 : 0;
		env->game.chunks = stack_sounds(env->game.chunks, 11, 0.5);
	}
	if (scancode == SDL_SCANCODE_SPACE && !env->game.player.my_entity.physic
		.fly)
		env->game.player.my_entity.physic.jump = 1;
	if (scancode == SDL_SCANCODE_F && (env->game.sectors[env->game.player.my_entity.physic.sector_id].ceiling.y < 0.01
		&& env->game.sectors[env->game.player.my_entity.physic.sector_id].ceiling.y > -0.01)
		&&(env->game.sectors[env->game.player.my_entity.physic.sector_id].ceiling.x < 0.01
		&& env->game.sectors[env->game.player.my_entity.physic.sector_id].ceiling.x > -0.01))
		env->game.player.my_entity.physic.fly = (env->game.player.my_entity
			.physic.fly) ? 0 : 1;
	if (!env->toggle_editor && (scancode == SDL_SCANCODE_KP_PLUS
		|| scancode == SDL_SCANCODE_EQUALS))
		env->editor.depth += 1;
	if (!env->toggle_editor && (scancode == SDL_SCANCODE_MINUS
		|| scancode == SDL_SCANCODE_KP_MINUS))
		env->editor.depth -= (env->editor.depth == 0) ? 0 : 1;
}

static void		keyactions(int scancode, t_env *env)
{
	env->events.key_click[scancode] = 1;
	if (scancode == SDL_SCANCODE_E && env->editor.enabled)
	{
		if (env->toggle_editor && (launch_check(env, env->game) == 1))
		{
			SDL_SetRelativeMouseMode(SDL_TRUE);
			env->toggle_editor = 0;
		}
		else
		{
			env->toggle_editor = 1;
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}
	if (env->editor.enabled && scancode == SDL_SCANCODE_Z)
	{
		if (env->file == NULL)
			env->file = "simple_map";
		save(env->file, env->game);
	}
	keyactions_2(scancode, env);
}

t_event			capture_events_loop(t_event events, t_env *env)
{
	SDL_Event	polled_event;
	static int	any = 0;

	events.any = any;
	while (SDL_PollEvent(&polled_event))
	{
		events.any = 1;
		if (polled_event.type == SDL_KEYDOWN)
		{
			any++;
			keyactions(polled_event.key.keysym.scancode, env);
			events.keys[polled_event.key.keysym.scancode] = 1;
		}
		else if (polled_event.type == SDL_KEYUP)
		{
			any--;
			events.keys[polled_event.key.keysym.scancode] = 0;
		}
		else if (polled_event.type == SDL_QUIT)
			events.quit = 1;
		events = mouse_event(events, polled_event, &any);
	}
	return (events);
}

t_event			capture_events(t_event events, t_env *env)
{
	events.wheel = 0;
	SDL_CaptureMouse(SDL_TRUE);
	events = capture_events_loop(events, env);
	if (ON_LINUX && !env->toggle_editor && env->game_mode != 0)
		SDL_WarpMouseInWindow(env->sdl.win, WIDTH / 2, HEIGHT / 2);
	SDL_CaptureMouse(SDL_FALSE);
	return (events);
}
