/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:20:56 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/04 15:54:07 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include "srcs/common/time_measure.h"

t_vec2		player_space(t_vec2 vec, t_ph physic)
{
	return (vec2_rot(vec2_sub(vec, vec3_to_vec2(physic.pos)), -physic.look_h));
}

static void	minimap(t_game game, t_color *buf)
{
	t_vec2	a;
	t_vec2	b;
	t_wall	wall;
	size_t	i;

	i = 0;
	while (i < game.nwalls)
	{
		wall = game.walls[i];
		a = game.points[wall.a];
		b = game.points[wall.b];
		a = player_space(a, game.player.physic);
		b = player_space(b, game.player.physic);
		bresenham(buf, (t_pix) {(a.u + 10) * 10, HEIGHT - (a.v + 10) * 10},
			(t_pix) {(b.u + 10) * 10, HEIGHT - (b.v + 10) * 10}, WHITE);
		i++;
	}
	a = player_space((t_vec2) {0, 0}, game.player.physic);
	b = player_space((t_vec2) {250, 0}, game.player.physic);
	bresenham(buf, (t_pix) {(a.u + 10) * 10, HEIGHT - (a.v + 10) * 10},
		(t_pix) {(b.u + 10) * 10, HEIGHT - (b.v + 10) * 10}, WHITE);
	a = player_space((t_vec2) {0, 0}, game.player.physic);
	b = player_space((t_vec2) {0, 250}, game.player.physic);
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
		a = player_space(a, game.player.physic);
		t_fvec2 a_f = vec2_to_fvec2(a);
		a_f = fvec2_scale(fvec2_add(a_f, fvec2_new(f_from_int(10), f_from_int(10))), f_from_int(10));
		draw_point(a_f,\
		2,buf, BLUE);
		i++;
	}
}

t_env		game_loop(t_env env, size_t frame)
{
	t_color			*content;
	int				pitch;
	double			timer;

	timer = start_timer();
	if (env.editor.enabled)
	
	env.game = game_editing(env.game, env.events, env.game.player, &env.sdl);
	env.game = player_properties(env.game, env.events);
	//env.game = entities_properties(env.game, env.events);
	env.game = physic(env.game, env.events);

	env.game.frame = frame;
	content = NULL;
	SDL_LockTexture(env.sdl.buf, NULL, (void **)&content, &pitch);
	env.current_buffer = content;
	background(env.current_buffer, NO_COLOR);
	render(
		env.game,
		(t_context) {
			0,
			WIDTH - 1,
			env.game.player.physic,
			-1,
			env.game.sectors[env.game.player.physic.sector_id]
		},
		env.current_buffer, env.game.id_buf);
	
	//raycast(env.game, env.game.player.physic.sector_id, env.current_buffer);
	minimap(env.game, env.current_buffer);
	SDL_UnlockTexture(env.sdl.buf);
	SDL_RenderCopy(env.sdl.renderer, env.sdl.buf, NULL, NULL);
	display_text(env.sdl);
	SDL_RenderPresent(env.sdl.renderer);
	timer = end_timer(timer);
	printf("%f\n", 1 / timer);
	return (env);
}
