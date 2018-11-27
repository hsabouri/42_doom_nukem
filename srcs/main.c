#include "../includes/SDL2/SDL.h"
#include <libft.h>
#include <stdio.h>
#include "../includes/test.h"

int main(void)
{
	SDL_Window		*win;
	SDL_Event		event;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	int         quit;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_putendl_fd(SDL_GetError(), STDERR_FILENO);
		return (-1);
	}

	win = NULL;
	win = SDL_CreateWindow("ft_doom_nukem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
	quit = 0;
	while (win && !quit)
	{
		SDL_WaitEvent(&event);

		if (event.type == SDL_QUIT)
			quit = 1;
	}
	if (!win)
	{
		ft_putendl_fd(SDL_GetError(), STDERR_FILENO);
		return (-1);
	}
	return (0);
}
