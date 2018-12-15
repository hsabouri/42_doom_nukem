/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:07:18 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/15 15:23:47 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_sdl	init_sdl(void)
{
	SDL_Window		*win;
	SDL_Texture		*buf;
	SDL_Renderer	*renderer;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit_error("Could not initialize SDL.");
	win = NULL;
	win = SDL_CreateWindow("doom_nukem", SDL_WINDOWPOS_UNDEFINED,\
		SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	buf = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,\
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	return ((t_sdl) {
		win,
		buf,
		renderer
	});
}

static void		game_loop(t_game game, size_t frame)
{
	t_color			*content;
	int				pitch;

	content = NULL;
	SDL_LockTexture(game.sdl.buf, NULL, (void **)&content, &pitch);
	for (int i = 0; i < HEIGHT; i++) {
		content[i * WIDTH + frame % WIDTH] = (t_color){ frame + 36 + 2 * i, frame * 3 - i, frame * -2, 0 };
	}
	SDL_UnlockTexture(game.sdl.buf);
	SDL_RenderCopy(game.sdl.renderer, game.sdl.buf, NULL, NULL);
	SDL_RenderPresent(game.sdl.renderer);
}

int main(void)
{
	t_game			game;
	size_t			frame;

	
	game.sdl = init_sdl();
	game.events = init_events();
	frame = 0;
	while (game.sdl.win)
	{
		game.events = capture_events(game.events);
		if (game.events.quit || game.events.keys[SDL_SCANCODE_ESCAPE])
			break;
		game_loop(game, frame);
		frame++;
	}
	if (!game.sdl.win)
		exit_error(SDL_GetError());
	return (0);
}
