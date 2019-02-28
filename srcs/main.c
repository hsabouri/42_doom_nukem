/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:07:18 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/16 17:00:46 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <load_save.h>

static TTF_Font	*init_font(void)
{
	TTF_Font	*font;

	if (TTF_Init() == -1)
	{
		console_error("SDL_ttf", "Could not init SDL_ttf");
		exit(EXIT_FAILURE);
	}
	if ((font = TTF_OpenFont("pressstart.ttf", 12)) != NULL)
		return (font);
	if ((font = TTF_OpenFont("arial.ttf", 12)) != NULL)
		return (font);
	console_error("SDL_ttf", TTF_GetError());
	exit(EXIT_FAILURE);
	return (font);
}

static t_sdl	init_sdl(void)
{
	SDL_Window		*win;
	SDL_Texture		*buf;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	t_array			text;

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
	font = init_font();
	SDL_SetRelativeMouseMode(SDL_TRUE);
	text = anew(NULL, NB_TEXT, sizeof(t_text));
	return ((t_sdl) {win, buf, renderer, font, text});
}

int				main(int ac, char **av)
{
	t_env		env;
	size_t		frame;

	if (ac == 3 && (ft_strcmp(av[2], "save")) == 0)
		return(main_save(av[1]));
	else if (ac == 3 && (ft_strcmp(av[2], "load")) == 0)
	{
		env.game = load(av[1]);
		launch_check(env.game);	
	}
	else
		env.game = generate_map(env.game);
	env.sdl = init_sdl();
	env.events = init_events();
	env.editor = init_editor();
	env.toggle_editor = 0;
	env.game.id_buf = (u_int32_t *)malloc(WIDTH * HEIGHT * sizeof(int));
	frame = 0;
	while (env.sdl.win)
	{
		env.events = capture_events(env.events, &env);
		if (!env.toggle_editor)
			env.game.player.physic = update_mouse(&env.events, env.game.player.physic);
		if (env.events.quit || env.events.keys[SDL_SCANCODE_ESCAPE])
			break ;
		if (env.toggle_editor)
			env = editor_loop(env, frame);
		else
			env = game_loop(env, frame);
		if (env.events.quit || env.events.keys[SDL_SCANCODE_ESCAPE])
			break ;
		env.events = reset_clicks(env.events);
		frame++;
	}
	if (!env.sdl.win)
	{
		console_error("doom_nukem", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return (0);
}
