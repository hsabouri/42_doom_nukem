/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:52:15 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/09 15:52:16 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void			clean(t_env env)
{
	clean_game(env.game);
	clean_texture(env);
	if (env.component)
		destroy_component(env.component);
	exit(EXIT_SUCCESS);
}

t_sdl			init_sdl(void)
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
