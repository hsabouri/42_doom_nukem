/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:07:18 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/27 18:27:39 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <load_save.h>

static t_sdl	init_sdl(void)
{
	SDL_Window		*win;
	SDL_Texture		*buf;
	SDL_Renderer	*renderer;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		console_error("doom_nukem", "Could not initialize SDL.");
		exit(EXIT_FAILURE);
	}
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

	game.current_buffer = content;
	aforeach_state(&game.walls, &display_wall, (void *)&game);

	SDL_UnlockTexture(game.sdl.buf);
	SDL_RenderCopy(game.sdl.renderer, game.sdl.buf, NULL, NULL);
	SDL_RenderPresent(game.sdl.renderer);
}

int				main(void)
{
	t_game			game;
	size_t			frame;

	game.sdl = init_sdl();
	game.events = init_events();
	game = generate_map(game);
	save("test.doom", game);
	frame = 0;
	while (game.sdl.win)
	{
		game.events = capture_events(game.events);
		if (game.events.quit || game.events.keys[SDL_SCANCODE_ESCAPE])
			break ;
		game_loop(game, frame);
		usleep(1000000 / 60); // 60 frame per second. Be careful here...
		frame++;
	}
	if (!game.sdl.win)
	{
		console_error("doom_nukem", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return (0);
}
