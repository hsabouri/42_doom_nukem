/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:04:16 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/24 17:32:14 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common.h"

static int					self_update(t_component *self, void *parent)
{
	t_button_state	*state;
	static int		last_to_activate_value = 0;
	int				ret;

	(void)parent;
	ret = 0;
	state = (t_button_state *)self->state;
	if (is_clicked_on(*self, *state->events) &&
		state->active_value != *state->to_activate)
	{
		*state->to_activate = state->active_value;
		ret = 1;
	}
	else if (state->active_value != *state->to_activate)
		ret = 1;
	last_to_activate_value = *state->to_activate;
	return (ret);
}

static void					self_render(const t_component self, t_color *buf)
{
	const t_button_state	*state = (t_button_state *)self.state;
	t_color					bg;

	bg = state->background;
	if (state->active_value == *state->to_activate)
	{
		bg.r = bg.r - 30;
		bg.g = bg.g - 30;
		bg.b = bg.b - 30;
	}
	background(buf, bg, self.size);
	component_image(self.img, (t_pix) {5, 5}, self.size, buf);
}

static t_button_state		*init_state(t_button button)
{
	t_button_state	*ret;

	ret = (t_button_state *)malloc(sizeof(t_button_state));
	ret->active_value = button.active_value;
	ret->background = button.background;
	ret->events = button.events;
	ret->to_activate = button.to_activate;
	return (ret);
}

t_component					init_button(t_button button, t_sdl *sdl)
{
	t_component ret;

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
	ret.state = init_state(button);
	ret.last_render = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, ret.size.x, ret.size.y);
	SDL_SetTextureBlendMode(ret.last_render, SDL_BLENDMODE_BLEND);
	ret.update = &self_update;
	ret.render = &self_render;
	ret.complete_render = NULL;
	ret.destroy = NULL;
	ret.childs = anew(NULL, 0, 1);
	return (ret);
}