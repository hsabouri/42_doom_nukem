/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:47:42 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/30 16:44:08 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	draw_point(t_fvec2 point, int s, t_color *buf, t_color c)
{
	int			i;
	int			j;
	const int	s_j = (f_to_int(point.u) - s >= 0) ? f_to_int(point.u) - s : 0;

	i = (f_to_int(point.v) - s >= 0) ? f_to_int(point.v) - s : 0;
	while (i < f_to_int(point.v) + s - 1 && i < HEIGHT)
	{
		j = s_j;
		while (j < f_to_int(point.u) + s - 1 && j < WIDTH)
		{
			buf[i * WIDTH + j] = c;
			j++;
		}
		i++;
	}
}

void	background(t_color *buf, t_color color, t_pix size)
{
	size_t			i;

	i = 0;
	while ((int)i < size.x * size.y)
	{
		buf[i] = color;
		i++;
	}
}

void	m_background(t_color *buf, t_color color, t_pix start, t_pix end)
{
	int		x;
	int		y;

	start = (t_pix) {
		(start.x >= 0) ? start.x : 0,
		(start.y >= 0) ? start.y : 0};
	end = (t_pix) {
		(end.x <= WIDTH) ? end.x : (WIDTH),
		(end.y <= HEIGHT) ? end.y : (HEIGHT)};
	x = start.x;
	while (x < end.x)
	{
		y = start.y;
		while (y < end.y)
		{
			buf[x + y * WIDTH] = color;
			++y;
		}
		++x;
	}
}

t_text	text(const char *str, t_pix pos, t_sdl *sdl)
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
	if (text_surface != NULL)
		SDL_FreeSurface(text_surface);
	sdl->text = *apush(&sdl->text, &text);
	return (text);
}
