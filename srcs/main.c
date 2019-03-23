/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:07:18 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/22 18:26:04 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <editor.h>
#include <doom.h>

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

void				clean_env(t_env env)
{
	Mix_CloseAudio();
	if (env.component)
		destroy_component(env.component);
}

int				main(int ac, char **av)
{
	t_env		env;
	size_t		frame;
	
	env.sdl = init_sdl();
	env.editor = init_editor();
	env.toggle_editor = 0;
	if (ac >= 2)
	{
		if (ft_strcmp(av[1], "editor") == 0)
		{
			if (ac == 3)
			{
				env.file = av[2];
				env.game = load(av[2], 1);
			}
			else
			{
				env.file = NULL;
				env.game = generate_map(env.game);	
			}
			launch_check(env.game);
			env.editor.enabled = 1;
		}
		else
		{
			env.file = av[1];
			env.game = load(av[1], 0);
			launch_check(env.game);
		}
	}
	else
	{
		env.file = NULL;
		env.game = generate_map(env.game);
		env.editor.enabled = 0;
	}
	env.game = init_audio(env.game);
	env.events = init_events();
	env.game.id_buf = (u_int32_t *)malloc(WIDTH * HEIGHT * sizeof(int));
	frame = 0;

	env.component = init_component(&env, &env.sdl);
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
		{
			env = game_loop(env, frame);
		}
		if (!env.sdl.win)
		{
			console_error("doom_nukem", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		env.events = reset_clicks(env.events);
		frame++;
	}
	clean_env(env);
	return (0);
}

