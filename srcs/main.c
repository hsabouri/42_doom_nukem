#include <SDL2/SDL.h>
#include <libft.h>
#include <doom.h>
#include <stdio.h>

#define WIDTH 640
#define HEIGHT 480

int main(void)
{
	SDL_Window		*win;
	SDL_Event		event;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	t_color			*content = NULL;
	int				pitch;
	int				quit;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_putendl_fd(SDL_GetError(), STDERR_FILENO);
		return (-1);
	}

	win = NULL;
	win = SDL_CreateWindow("ft_doom_nukem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

	SDL_LockTexture(texture, NULL, (void **)&content, &pitch);
	for (int i = 0; i < HEIGHT; i++) {
		content[i * WIDTH + 100] = (t_color){ 142, 77, 226, 0 };
	}
	SDL_UnlockTexture(texture);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

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
