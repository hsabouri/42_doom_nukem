/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_button.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 12:13:01 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/26 12:13:05 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common.h"

static int				self_update(t_component *self, void* parent)
{
	t_cb_button_state	*state;
	int					ret;
	
	(void)parent;
	ret = 0;
	state = (t_cb_button_state *)self->state;
	if (((state->events)->keys[state->scancode]) ||
		is_clicked_on(*self, *state->events))
	{
		state->is_active = 1;
		ret = 1;
	}
	else if (!(is_clicked_on(*self, *state->events)) && state->is_active)
	{
		ret = state->callback(parent);
		state->is_active = 0;
	}
	return (ret);
}

static void				self_render(const t_component self, t_color *buf)
{
	const t_cb_button_state	*state = (t_cb_button_state *)self.state;
	t_color					bg;

	bg = state->background;
	if (state->is_active)
	{
		bg.r = bg.r - 30;
		bg.g = bg.g - 30;
		bg.b = bg.b - 30;
	}
	background(buf, bg, self.size);
	component_image(self.img, (t_pix) {5, 5}, self.size, buf);
}

static t_cb_button_state	*init_stat(t_cb_button button)
{
	t_cb_button_state	*ret;

	ret = (t_cb_button_state *)malloc(sizeof(t_cb_button_state));
	ret->background = button.background;
	ret->events = button.events;
	ret->is_active = 0;
	ret->callback = button.callback;
	ret->scancode = button.scancode;
	return (ret);
}

t_component				init_cb_button(t_cb_button button, t_sdl *sdl)
{
	t_component	ret;

	ret.img.content = NULL;
	ret.text.text_texture = NULL;
	ret.size = button.size;
	if (button.img.content)
		ret.img = button.img;
	else if (button.place_holder)
	{
		ret.text = component_text(button.place_holder, (t_pix) {5, 5}, sdl);
		ret.size.x = ret.text.w + 6;
		ret.size.y = ret.text.h + 6;
	}
	ret.pos = button.pos;
	ret.display = 1;
	ret.state = init_stat(button);
	ret.update = &self_update;
	ret.render = &self_render;
	ret.complete_render = NULL;
	ret.destroy = NULL;
	ret.childs = anew(NULL, 0, 1);
	ret.last_render = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, ret.size.x, ret.size.y);
	SDL_SetTextureBlendMode(ret.last_render, SDL_BLENDMODE_BLEND);
	return (ret);
}
