/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 14:20:56 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/05 14:32:48 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_env	game_loop(t_env env, size_t frame)
{
	t_color			*content;
	size_t			i;
	int				pitch;

	env.game = physic(env.game, env.events);
	content = NULL;
	SDL_LockTexture(env.sdl.buf, NULL, (void **)&content, &pitch);
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		content[i] = NO_COLOR;
		i++;
	}
	env.current_buffer = content;
	i = 0;
	while (i < env.game.nsectors)
	{
		display_sector(env.game.sectors[i], env.game, env.current_buffer);
		i++;
	}
	SDL_UnlockTexture(env.sdl.buf);
	SDL_RenderCopy(env.sdl.renderer, env.sdl.buf, NULL, NULL);
	SDL_RenderPresent(env.sdl.renderer);
	return (env);
}
