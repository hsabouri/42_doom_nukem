/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:47:42 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/17 13:31:46 by hsabouri         ###   ########.fr       */
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

t_text				text(const char *str, t_pix pos, t_sdl *sdl)
{
	SDL_Surface	*text_surface;
	t_text		text;

	text.x = pos.x;
	text.y = pos.y;
	text_surface = TTF_RenderText_Shaded(sdl->font, str,\
		(SDL_Color){255, 255, 255, 255}, (SDL_Color){0, 0, 0, 0});
	SDL_SetColorKey(text_surface, SDL_TRUE, 0);
	text.text_texture = SDL_CreateTextureFromSurface(sdl->renderer,\
		text_surface);
	SDL_QueryTexture(text.text_texture, NULL, NULL, &text.w, &text.h);
	SDL_FreeSurface(text_surface);
	sdl->text = *apush(&sdl->text, &text);
	return (text);
}

void				display_text(t_sdl sdl)
{
	t_text	*current;

	while ((current = (t_text*)apop(&sdl.text)))
	{
		SDL_RenderCopy(sdl.renderer, current->text_texture, NULL,\
			&((SDL_Rect) {current->x, current->y, current->w * 0.8,\
			current->h}));
		SDL_DestroyTexture(current->text_texture);
	}
}
