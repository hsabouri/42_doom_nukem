/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:07:18 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/29 17:57:34 by hsabouri         ###   ########.fr       */
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

static void		game_loop(t_env env, size_t frame)
{
	t_color			*content;
	size_t			i;
	int				pitch;

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
	while (i < env.game.nwalls)
	{
		display_wall(env.game.walls[i], env.game, env.current_buffer);
		i++;
	}

	SDL_UnlockTexture(env.sdl.buf);
	SDL_RenderCopy(env.sdl.renderer, env.sdl.buf, NULL, NULL);
	SDL_RenderPresent(env.sdl.renderer);
}

int				main(void)
{
	t_env		env;
	size_t		frame;

	env.sdl = init_sdl();
	env.events = init_events();
	env.game = generate_map(env.game);
	//save("test.doom", game);
	frame = 0;
	while (env.sdl.win)
	{
		env.events = capture_events(env.events);
		if (env.events.quit || env.events.keys[SDL_SCANCODE_ESCAPE])
			break ;
		game_loop(env, frame);
		usleep(1000000 / 60); // 60 frame per second. Be careful here...
		frame++;
	}
	if (!env.sdl.win)
	{
		console_error("doom_nukem", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return (0);
}
