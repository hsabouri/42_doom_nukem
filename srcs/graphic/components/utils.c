/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:11:18 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/27 10:58:21 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_text			component_text(const char *str, t_pix pos, t_sdl *sdl)
{
	SDL_Surface	*text_surface;
	t_text		text;

	text.x = pos.x;
	text.y = pos.y;
	text_surface = TTF_RenderText_Shaded(sdl->font, str,
		(SDL_Color){255, 255, 255, 255}, (SDL_Color){70, 70, 70, 0});
	SDL_SetColorKey(text_surface, SDL_TRUE, 0);
	text.text_texture = SDL_CreateTextureFromSurface(sdl->renderer,
		text_surface);
	SDL_QueryTexture(text.text_texture, NULL, NULL, &text.w, &text.h);
	if (text_surface != NULL)
		SDL_FreeSurface(text_surface);
	return (text);
}

void			component_image(const t_img img, t_pix pos,
const t_pix buf_size, t_color *buf)
{
	size_t x;
	size_t y;

	if (img.content)
	{
		x = pos.x;
		while (x < img.width + pos.x && x < (size_t)buf_size.x)
		{
			y = pos.y;
			while (y < img.height + pos.y && y < (size_t)buf_size.y)
			{
				if (img.content[x - pos.x + (y - pos.y) * img.width].a > 0)
					buf[x + y * buf_size.x] = img.content[x - pos.x + (y
					- pos.y) * img.width];
				y++;
			}
			x++;
		}
	}
}

SDL_Texture		*empty_render(t_component any, t_sdl *sdl)
{
	(void)sdl;
	(void)any;
	return (NULL);
}

void			no_destroy(t_component *self)
{
	(void)self;
	return ;
}

t_component		default_component(void *state_address, t_pix size, t_sdl *sdl)
{
	t_component ret;

	ret.img.content = NULL;
	ret.text.text_texture = NULL;
	ret.size = size;
	ret.pos.x = 0;
	ret.pos.y = 0;
	ret.display = 1;
	ret.state = state_address;
	ret.update = NULL;
	if (ret.state)
		ret.destroy = NULL;
	else
		ret.destroy = &no_destroy;
	ret.render = NULL;
	ret.complete_render = NULL;
	ret.last_render = NULL;
	if (size.x && size.y)
		ret.last_render = SDL_CreateTexture(sdl->renderer,
			SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
			size.x, size.y);
	SDL_SetTextureBlendMode(ret.last_render, SDL_BLENDMODE_BLEND);
	return (ret);
}
