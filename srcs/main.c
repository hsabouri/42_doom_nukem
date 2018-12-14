/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:07:18 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/14 18:17:57 by hsabouri         ###   ########.fr       */
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

int main(void)
{
	t_game			game;
	SDL_Event		event;
	t_color			*content = NULL;
	int				pitch;
	int				quit;

	
	game.sdl = init_sdl();
	SDL_LockTexture(game.sdl.buf, NULL, (void **)&content, &pitch);
	for (int i = 0; i < HEIGHT; i++) {
		content[i * WIDTH + 100] = (t_color){ 142, 77, 226, 0 };
	}
	SDL_UnlockTexture(game.sdl.buf);
	SDL_RenderCopy(game.sdl.renderer, game.sdl.buf, NULL, NULL);
	SDL_RenderPresent(game.sdl.renderer);

	quit = 0;
	while (game.sdl.win && !quit)
	{
		SDL_WaitEvent(&event);

		if (event.type == SDL_QUIT)
			quit = 1;
	}
	if (!game.sdl.win)
	{
		ft_putendl_fd(SDL_GetError(), STDERR_FILENO);
		return (-1);
	}
	return (0);
}
