/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:19:28 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/03 17:42:22 by fmerding         ###   ########.fr       */
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

static void		keyactions(int scancode, t_env *env)
{
	env->events.key_click[scancode] = 1;
	if (scancode == SDL_SCANCODE_E && env->editor.enabled)
	{
		if (env->toggle_editor)
		{
			launch_check(env->game);
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
			env->file = "default";
		save(env->file, env->game);
	}
	if (scancode == SDL_SCANCODE_SPACE && !env->game.player.my_entity.physic.fly)
		env->game.player.my_entity.physic.jump = 1;
	if (scancode == SDL_SCANCODE_F)
		env->game.player.my_entity.physic.fly = (env->game.player.my_entity.physic.fly) ? 0 : 1;
	// if (env->toggle_editor && scancode == SDL_SCANCODE_O)
	// 	env->editor.current_tool = WALL;
	// if (env->toggle_editor && scancode == SDL_SCANCODE_P)
	// 	env->editor.current_tool = POINT;
	// if (env->toggle_editor && scancode == SDL_SCANCODE_I)
	// 	env->editor.current_tool = PORTAL;
	if (scancode == SDL_SCANCODE_M)
		env->game.played_music = (env->game.played_music == 0) ? 1 : 0;
	if (!env->toggle_editor &&
		(scancode == SDL_SCANCODE_KP_PLUS || scancode == SDL_SCANCODE_EQUALS))
		env->editor.depth += 1;
	if (!env->toggle_editor &&
		(scancode == SDL_SCANCODE_MINUS || scancode == SDL_SCANCODE_KP_MINUS))
		env->editor.depth -= (env->editor.depth == 0) ? 0 : 1;
	if (scancode == SDL_SCANCODE_KP_6)
	{
		find_center_sectors(env->game);
		rotate_floor(env->game.player.my_entity.physic.sector_id, 1, env->game);
	}
	if (scancode == SDL_SCANCODE_KP_4)
	{
		find_center_sectors(env->game);
		rotate_floor(env->game.player.my_entity.physic.sector_id, 2, env->game);
	}
	if (scancode == SDL_SCANCODE_KP_8)
	{
		find_center_sectors(env->game);
		rotate_floor(env->game.player.my_entity.physic.sector_id, 3, env->game);
	}
	if (scancode == SDL_SCANCODE_KP_2)
	{
		find_center_sectors(env->game);
		rotate_floor(env->game.player.my_entity.physic.sector_id, 4, env->game);
	}
	if (scancode == SDL_SCANCODE_KP_7)
	{
		find_center_sectors(env->game);
		rotate_ceiling(env->game.player.my_entity.physic.sector_id, 1, env->game);
	}
	if (scancode == SDL_SCANCODE_KP_9)
	{
		find_center_sectors(env->game);
		rotate_ceiling(env->game.player.my_entity.physic.sector_id, 2, env->game);
	}
	if (scancode == SDL_SCANCODE_KP_1)
	{
		find_center_sectors(env->game);
		rotate_ceiling(env->game.player.my_entity.physic.sector_id, 3, env->game);
	}
	if (scancode == SDL_SCANCODE_KP_3)
	{
		find_center_sectors(env->game);
		rotate_ceiling(env->game.player.my_entity.physic.sector_id, 4, env->game);
	}
	// if (scancode == SDL_SCANCODE_KP_0)
	// {
	// 	find_center_sectors(env->game);
	// 	rotate_floor(env->game.player.my_entity.physic.sector_id, 0, env->game);
	// 	rotate_ceiling(env->game.player.my_entity.physic.sector_id, 0, env->game);
	// }
}

t_event			capture_events(t_event events, t_env *env)
{
	SDL_Event	polled_event;
	static int	any = 0;

	events.wheel = 0;
	events.any = any;
	SDL_CaptureMouse(SDL_TRUE);
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
	if (ON_LINUX && !env->toggle_editor && env->game_mode != 0)
		SDL_WarpMouseInWindow(env->sdl.win, WIDTH / 2, HEIGHT / 2);
	SDL_CaptureMouse(SDL_FALSE);
	return (events);
}
