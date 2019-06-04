/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:20:56 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/03 10:22:33 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <editor.h>
#include "srcs/common/time_measure.h"

t_vec2		player_space(t_vec2 vec, t_ph physic)
{
	return (vec2_rot(vec2_sub(vec, vec3_to_vec2(physic.pos)), -physic.look_h));
}

void		minimap(t_game game, t_color *buf)
{
	t_vec2	a;
	t_vec2	b;
	t_wall	wall;
	t_color color;
	size_t	i;

	i = 0;
	while (i < game.nwalls)
	{
		wall = game.walls[i];
		a = game.points[wall.a];
		b = game.points[wall.b];
		a = player_space(a, game.player.my_entity.physic);
		b = player_space(b, game.player.my_entity.physic);
		bresenham(buf, (t_pix) {(a.u + 10) * 10, HEIGHT - (a.v + 10) * 10},
			(t_pix) {(b.u + 10) * 10, HEIGHT - (b.v + 10) * 10}, WHITE);
		i++;
	}
	a = player_space((t_vec2) {0, 0}, game.player.my_entity.physic);
	b = player_space((t_vec2) {250, 0}, game.player.my_entity.physic);
	bresenham(buf, (t_pix) {(a.u + 10) * 10, HEIGHT - (a.v + 10) * 10},
		(t_pix) {(b.u + 10) * 10, HEIGHT - (b.v + 10) * 10}, WHITE);
	a = player_space((t_vec2) {0, 0}, game.player.my_entity.physic);
	b = player_space((t_vec2) {0, 250}, game.player.my_entity.physic);
	bresenham(buf, (t_pix) {(a.u + 10) * 10, HEIGHT - (a.v + 10) * 10},
		(t_pix) {(b.u + 10) * 10, HEIGHT - (b.v + 10) * 10}, WHITE);
	bresenham(buf, (t_pix) {100, HEIGHT - 100}, (t_pix) {100, HEIGHT - 110}, RED);
	bresenham(buf, (t_pix) {95, HEIGHT - 100}, (t_pix) {105, HEIGHT - 100}, RED);
	draw_point((t_fvec2) {f_from_int(WIDTH / 2), f_from_int(HEIGHT / 2)},\
		1, buf, RED);
	i = 0;
	while (i < game.nentities)
	{
		a = vec3_to_vec2(game.entities[i].physic.pos);
		a = player_space(a, game.player.my_entity.physic);
		t_fvec2 a_f = vec2_to_fvec2(a);
		if (game.entities[i].damage == 0)
			color = BLUE;
		else
			color = RED;
		a_f.u = f_add_int(a_f.u, 10) * 10;
		a_f.v = f_from_int(HEIGHT) - f_add_int(a_f.v, 10) * 10;
		draw_point(a_f, 2, buf, color);
		i++;
	}
}


t_game		check_see(t_game game)
{
	t_game n_game;
	t_trigger tmp_log;
	t_selected ren;
	n_game = game;

	ren = world_selector(n_game);
	if (ren.type == PART_ENTITY)
	{
		tmp_log.e_actif = n_game.player.my_entity;
		tmp_log.condi = TRIGGER_SEE;
		tmp_log.e_passif = n_game.entities[ren.id];
		apush(&n_game.log, &tmp_log);
	}
	return (n_game);
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
	//env->game = entities_properties(env->game, env->events);
	env->game = check_see(env->game);
	if (env->game.nwalls > 0)
		env->game = physic(env->game, env->events, old_timer);
	env->game.frame = frame;
	env->game = check_conditions(env->game, env->events, env->condition);
	content = NULL;
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
	old_timer = end_timer(timer);
}
