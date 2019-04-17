/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:07:18 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/16 11:04:19 by hugo             ###   ########.fr       */
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
	if ((font = TTF_OpenFont("assistant.ttf", 16)) != NULL)
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
	text = safe_anew(NULL, NB_TEXT, sizeof(t_text), "doom_nukem");
	return ((t_sdl) {win, buf, renderer, font, text});
}

void				clean(t_env env)
{
	clean_game(env.game);
	clean_texture(env);
	if (env.component)
		destroy_component(env.component);
	exit(EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	t_env		env;
	size_t		frame;
	
	env.sdl = init_sdl();
	env.editor = init_editor();
	env.toggle_editor = 0;
	env.events = init_events();
	env.component = init_menu(&env, &env.sdl);
	*env.component = render_all(*env.component, &env.sdl);
	env.game_mode = 0;
	env.init_game = 1;	
	frame = 0;
	while (env.sdl.win)
	{
		env.events = capture_events(env.events, &env);
		if (env.init_game && (env.game_mode == 1 || env.game_mode == 2))
		{
			if (ac == 2 && env.game_mode == 1)
				{
					env.file = av[1];
					env.game = load(av[1], 0);
				}
				else
				{
					env.file = NULL;
					env.game = generate_map();
				}
				launch_check(env.game);
			env.game = init_audio(env.game);
			env.game.id_buf = (u_int32_t *)safe_malloc((WIDTH * HEIGHT * sizeof(int)), "doom_nukem");
			if (env.component)
				destroy_component(env.component);
			env.component = init_component(&env, &env.sdl);
			env.init_game = 0;
		}
		if (!env.toggle_editor)
			env.game.player.physic = update_mouse(&env.events, env.game.player.physic);
		if (env.events.quit || env.game_mode == -1 ||
			env.events.keys[SDL_SCANCODE_ESCAPE])
			break ;
		if (env.game_mode == 0)
			env = menu_loop(env, frame);
		else if (env.game_mode == 1 || env.game_mode == 2)
		{
			if (!env.toggle_editor)
				env = game_loop(env, frame);
			else
				env = editor_loop(env, frame);
		}
		if (!env.sdl.win)
		{
			console_error("doom_nukem", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		env.events = reset_clicks(env.events);
		frame++;
	}
	clean(env);
	return (0);
}

