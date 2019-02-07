/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:47:42 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/05 11:55:09 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void				draw_point(t_fvec2 point, int s, t_color *buf, t_color c)
{
	int			i;
	int			j;
	const int	s_j = (f_to_int(point.u) - s >= 0) ? f_to_int(point.u) - s : 0;

	i = (f_to_int(point.v) - s >= 0) ? f_to_int(point.v) - s : 0;
	while (i < f_to_int(point.v) + s && i < HEIGHT)
	{
		j = s_j;
		while (j < f_to_int(point.u) + s && j < WIDTH)
		{
			buf[i * WIDTH + j] = c;
			j++;
		}
		i++;
	}
}

void				background(t_color *buf, t_color color)
{
	size_t			i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		buf[i] = color;
		i++;
	}
}

t_pix				text(const char *str, t_pix pos, t_sdl sdl)
{
	SDL_Surface	*text_surface;
	SDL_Texture	*text_texture;
	int			w;
	int			h;

	text_surface = TTF_RenderText_Shaded(sdl.font, str,\
		(SDL_Color){255, 255, 255, 255}, (SDL_Color){0, 20, 33, 255});
	text_texture = SDL_CreateTextureFromSurface(sdl.renderer, text_surface);
	SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);
	SDL_RenderCopy(sdl.renderer, text_texture, NULL,\
		&((SDL_Rect) {pos.x, pos.y, w, h}));
	SDL_DestroyTexture(text_texture);
	SDL_FreeSurface(text_surface);
	return ((t_pix) {w, h});
}
