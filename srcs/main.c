/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:07:18 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/16 13:24:51 by hsabouri         ###   ########.fr       */
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

int				main(void)
{
	t_env		env;
	size_t		frame;

	env.sdl = init_sdl();
	env.events = init_events();
	env.game = generate_map(env.game);
	frame = 0;
	while (env.sdl.win)
	{
		env.events = capture_events(env.events, &env);
		env.game.player.physic = update_mouse(&env.events, env.game.player.physic);
		if (env.events.quit || env.events.keys[SDL_SCANCODE_ESCAPE])
			break ;
		if (env.toggle_editor)
			env = editor_loop(env, frame);
		else
			env = game_loop(env, frame);
		if (env.events.quit || env.events.keys[SDL_SCANCODE_ESCAPE])
			break ;
		frame++;
	}
	if (!env.sdl.win)
	{
		console_error("doom_nukem", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return (0);
}
