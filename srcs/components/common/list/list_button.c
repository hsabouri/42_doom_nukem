/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:54:32 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/27 12:03:16 by hsabouri         ###   ########.fr       */
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

static t_list_button_state	*init_state(t_list_button button,
t_list_state state)
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
	ret->destroy_image = state.destroy_image;
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
			.pos = (t_pix) {p->pos.x + p->size.x,
				p->pos.y + 1 - state.y_scroll},
			.size = (t_pix) {30, 29}, .background = state.bg,
			.events = state.events, .place_holder = NULL,
			.callback = &self_del, .scancode = SDL_SCANCODE_UNKNOWN,
			.img = parse_tga("./textures/ui/cross.tga", 0)}, sdl);
		apush(&childs, &current);
	}
	else
		childs = safe_anew(NULL, 0, sizeof(t_component), "components");
	return (childs);
}

void						self_destroy(t_component *component)
{
	t_list_button_state	*state;

	state = (t_list_button_state *)component->state;
	if (!state->destroy_image)
		component->img.content = NULL;
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
	if (button.text[0])
		ret.text = component_text(button.text, (t_pix) {5, 5}, sdl);
	ret.pos = button.pos;
	ret.display = 1;
	ret.state = init_state(button, state);
	ret.update = &update_list_button;
	ret.render = &render_list_button;
	ret.complete_render = NULL;
	ret.destroy = &self_destroy;
	ret.childs = init_childs(&ret, state, sdl);
	ret.last_render = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, ret.size.x, ret.size.y);
	SDL_SetTextureBlendMode(ret.last_render, SDL_BLENDMODE_BLEND);
	return (ret);
}
