/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:04:16 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/22 16:11:15 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common.h"

static int					self_update(t_component *self, void *parent)
{
	t_button_state	*state;
	int				ret;

	(void)parent;
	ret = 1;
	state = (t_button_state *)self->state;
	if (((state->scancode != SDL_SCANCODE_UNKNOWN
		&& state->events->keys[state->scancode])
		|| (is_clicked_on(*self, *state->events)
		&& state->active_value != *state->to_activate)))
		state->is_active = 1;
	else if (!(is_clicked_on(*self, *state->events))
		&& state->active_value != *state->to_activate && state->is_active)
	{
		*state->to_activate = state->active_value;
		(*state->events).keys[state->scancode] = 0;
		state->is_active = 0;
	}
	else if (is_over(*self, *state->events))
		ret = 1;
	else if (!(is_over(*self, *state->events)))
		ret = 1;
	else
		ret = 0;
	return (ret);
}

static void					self_render(t_component self, t_color *buf)
{
	const t_button_state	*state = (t_button_state *)self.state;
	t_color					bg;
	t_img					img;

	bg = state->background;
	img = self.img;
	if (is_over(self, *state->events) && state->img_active.content)
		img = state->img_active;
	if (state->active_value == *state->to_activate)
	{
		bg.r = bg.r - 30;
		bg.g = bg.g - 30;
		bg.b = bg.b - 30;
	}
	background(buf, bg, self.size);
	if (img.content)
		component_image(img, (t_pix) {5, 5}, self.size, buf);
}

static t_button_state		*init_state(t_button button)
{
	t_button_state	*ret;

	ret = (t_button_state *)safe_malloc(sizeof(t_button_state), "components");
	ret->active_value = button.active_value;
	ret->background = button.background;
	ret->events = button.events;
	ret->to_activate = button.to_activate;
	ret->is_active = 0;
	ret->scancode = button.scancode;
	ret->img_active.content = NULL;
	if (button.img_active.content)
		ret->img_active = button.img_active;
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
		ret.text = component_text(button.place_holder, (t_pix) {8, 3}, sdl);
		ret.size.x = ret.text.w + 16;
		ret.size.y = ret.text.h + 8;
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
	ret.destroy = &destroy_button;
	ret.childs = safe_anew(NULL, 0, 1, "components");
	return (ret);
}
