/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:54:32 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/09 12:15:12 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./list_comp.h"

static int					self_del(void *button)
{
	t_list_button_state	*state;

	state = (t_list_button_state *)button;
	state->list->need_update = state->del(state->parent, state->i);
	return (0);
}

static int					self_update(t_component *self, void* parent)
{
	t_list_state		*list_state;
	t_list_button_state	*state;
	int					ret;
	int					clicked;
	
	ret = 0;
	state = (t_list_button_state *)self->state;
	list_state = (t_list_state *)parent;
	state->parent = list_state->parent;
	state->list = list_state;
	self->pos.y = state->d_pos.y - *state->y_scroll;
	if (self->childs.len)
		((t_component *)self->childs.first)->pos.y =
			state->d_pos.y - *state->y_scroll + 1;
	clicked = is_clicked_on(*self, *state->events);
	if (clicked && state->is_active == 0 && state->select)
	{
		state->is_active = 1;
		ret = 1;
	}
	if (!clicked && state->is_active && state->select)
	{
		list_state->need_update = state->select(list_state->parent, state->i);
		state->is_active = 0;
		ret = 1;
	}
	if (!clicked && state->events->any)
		ret = 1;
	return (ret);
}

static void					self_render(const t_component self, t_color *buf)
{
	const t_list_button_state	*state = (t_list_button_state *)self.state;
	t_color						bg;
	t_color						outline;

	bg = state->bg;
	outline.r = bg.r - 30;
	outline.g = bg.g - 30;
	outline.b = bg.b - 30;
	outline.a = 255;
	if (state->is_active)
		bg = outline;
	background(buf, bg, self.size);
	background(buf, outline, (t_pix) {self.size.x, 1});
	if (self.img.content)
		component_image(self.img, (t_pix) {5, 5}, self.size, buf);
}

static t_list_button_state	*init_state(t_list_button button, t_list_state state)
{
	t_list_button_state	*ret;

	ret = (t_list_button_state *)safe_malloc(sizeof(t_list_button_state),
		"components");
	ret->i = button.i;
	ret->del = state.del;
	ret->select = state.select;
	ret->is_active = 0;
	ret->events = state.events;
	ret->parent = button.parent;
	ret->bg = state.bg;
	ret->d_pos = button.pos;
	ret->y_scroll = button.y_scroll;
	return (ret);
}

static t_array				init_childs(t_component *p, t_list_state state,\
t_sdl *sdl)
{
	t_array		childs;
	t_component	current;

	if (state.del)
	{
		p->size.x -= 30;
		childs = safe_anew(NULL, 1, sizeof(t_component), "components");
		current = init_cb_button((t_cb_button) {
			.pos = (t_pix) {p->pos.x + p->size.x, p->pos.y + 1 - state.y_scroll},
			.size = (t_pix) {30, 29}, .background = state.bg,
			.events = state.events, .place_holder = NULL,
			.callback = &self_del, .scancode = SDL_SCANCODE_UNKNOWN,
			.img = parse_tga("./textures/ui/cross.tga")}, sdl);
		apush(&childs, &current);
	}
	else
		childs = safe_anew(NULL, 0, sizeof(t_component), "components");
	return (childs);
}

t_component					init_list_button(t_list_button button,
t_list_state state, t_sdl *sdl)
{
	t_component	ret;

	ret.text.text_texture = NULL;
	ret.img.content = NULL;
	ret.size = button.size;
	if (button.img.content)
		ret.img = button.img;
	else if (button.text[0])
		ret.text = component_text(button.text, (t_pix) {5, 5}, sdl);
	ret.pos = button.pos;
	ret.display = 1;
	ret.state = init_state(button, state);
	ret.update = &self_update;
	ret.render = &self_render;
	ret.complete_render = NULL;
	ret.destroy = NULL;
	ret.childs = init_childs(&ret, state, sdl);
	ret.last_render = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, ret.size.x, ret.size.y);
	SDL_SetTextureBlendMode(ret.last_render, SDL_BLENDMODE_BLEND);
	return (ret);
}
