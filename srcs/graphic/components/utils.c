/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:11:18 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/21 14:18:21 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_text			component_text(const char *str, t_pix pos, t_sdl *sdl)
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
	return (text);
}

void			component_image(const t_img img, t_pix pos,
const t_pix buf_size, t_color *buf)
{
	int x;
	int y;

	x = pos.x;
	while (x < img.width + pos.x && x < buf_size.x)
	{
		y = pos.y;
		while (y < img.height + pos.y && y < buf_size.y)
		{
			buf[x + y * buf_size.x] =
				img.content[x - pos.x + (y - pos.y) * img.width];
			y++;
		}
		x++;
	}
}