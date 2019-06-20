/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:20:56 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/19 13:20:32 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <editor.h>
#include "srcs/common/time_measure.h"

t_vec2		player_space(t_vec2 vec, t_ph physic)
{
	return (vec2_rot(vec2_sub(vec, vec3_to_vec2(physic.pos)), -physic.look_h));
}

void		game_loop(t_env *env, size_t frame)
{
	t_color			*content;
	int				pitch;
	float			timer;
	static float	old_timer = 1;

	timer = start_timer();
	if (env->editor.enabled)
		*env = game_editing(*env, env->game.player);
	env->game = player_properties(env->game, env->events);
	if (env->game.nwalls > 0)
		env->game = physic(env->game, env->events, old_timer);
	env->game.frame = frame;
	env = event_action(env, &env->events, env->game.id_buf);
	env->game = animate(env->game, old_timer);
	SDL_LockTexture(env->sdl.buf, NULL, (void **)&content, &pitch);
	env->current_buffer = content;
	if (env->game.nwalls > 0)
		render_multi_threaded(*env, env->current_buffer);
	SDL_UnlockTexture(env->sdl.buf);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.buf, NULL, NULL);
	*env->component = trigger_component(env, *env->component, &env->sdl);
	display_component(*env->component, &env->sdl);
	play_music(env->game, env->game.played_music, 0, frame);
	env->game = play_sounds(env->game);
	SDL_RenderPresent(env->sdl.renderer);
	env->game = play_sounds(env->game);
	printf("%f\n", old_timer);
	old_timer = end_timer(timer);
}
