/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:20:56 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/17 13:58:50 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_vec2		player_space(t_vec2 vec, t_ph physic)
{
	return (vec2_rot(vec2_sub(vec, vec3_to_vec2(physic.pos)), -physic.look.u));
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
		bresenham(buf, (t_pix) {(a.u + 10) * 10, (a.v + 10) * 10},
			(t_pix) {(b.u + 10) * 10, (b.v + 10) * 10}, WHITE);
		i++;
	}
	bresenham(buf, (t_pix) {100, 100}, (t_pix) {100, 110}, RED);
	bresenham(buf, (t_pix) {95, 100}, (t_pix) {105, 100}, RED);
}

t_env		game_loop(t_env env, size_t frame)
{
	t_color			*content;
	size_t			i;
	int				pitch;

	env.game = physic(env.game, env.events);
	env.game.frame = frame;
	content = NULL;
	SDL_LockTexture(env.sdl.buf, NULL, (void **)&content, &pitch);
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		content[i] = NO_COLOR;
		i++;
	}
	env.current_buffer = content;
	raycast(env.game, env.game.player.physic.sector_id, env.current_buffer);
	minimap(env.game, env.current_buffer);
	SDL_UnlockTexture(env.sdl.buf);
	SDL_RenderCopy(env.sdl.renderer, env.sdl.buf, NULL, NULL);
	SDL_RenderPresent(env.sdl.renderer);
	return (env);
}
