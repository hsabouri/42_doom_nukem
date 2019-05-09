/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_comp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:36:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/09 12:14:46 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./list_comp.h"

static t_array		clean_old(t_component *self, t_list_state *state,
t_array built)
{
	t_array			ret;
	const size_t	new_size = built.len + ((state->add) ? 1 : 0);

	ret = safe_anew(NULL, new_size, sizeof(t_component), "components");
	if (state->add)
		apush(&ret, ashift(&self->childs));
	if (self->childs.len)
		clean_childs(self->childs);
	return (ret);
}

static t_array		build_childs(t_component *self, t_list_state *state,
void *parent, t_sdl *sdl)
{
	t_array			built;
	t_list_content	*current;
	t_list_button	button;
	t_component		current_comp;
	size_t			i;

	built = state->build(parent);
	self->childs = clean_old(self, state, built);
	i = (size_t)-1;
	while ((current = (t_list_content *)apop(&built)) && i++ <= (size_t)-1)
	{
		button = (t_list_button) {.i = i, .parent = parent,
			.pos = (t_pix) {self->pos.x + 1, self->pos.y + 41 + 31 * i},
			.size = (t_pix) {self->size.x - 2, 30}, .img = current->img,
			.y_scroll = &state->y_scroll};
		strncpy(button.text, current->text, 28);
		current_comp = init_list_button(button, *state, sdl);
		render_all(current_comp, sdl);
		apush(&self->childs, &current_comp);
	}
	if (built.mem)
		free(built.mem);
	return (self->childs);
}

static int			self_add(void *self_state)
{
	t_list_state 		*state;
	int					ret;

	state = (t_list_state *)self_state;
	ret = state->add(state->parent);
	state->need_update = ret;
	return (ret);
}

static int			self_update(t_component *self, void *parent)
{
	t_list_state	*state;
	int				ret;

	ret = 0;
	state = (t_list_state *)self->state;
	state->parent = parent;
	if (is_over(*self, *state->events) && (state->y_scroll > 0 || state->events->wheel > 0))
		state->y_scroll += state->events->wheel * 100;
	if (state->need_update)
	{
		self->childs = build_childs(self, state, parent, state->sdl);
		state->need_update = 0;
		ret = 1;
	}
	if (state->events->any)
		ret = 1;
	return (ret);
}

static void			self_render(t_component self, t_color *buf)
{
	const t_list_state *state = (t_list_state *)self.state;

	background(buf, state->bg, (t_pix) {self.size.x, 40});
}

static t_array		init_childs (t_list_comp list, t_sdl *sdl)
{
	t_array		childs;
	t_component	current;

	childs = safe_anew(NULL, 2, sizeof(t_component), "component");
	current = init_cb_button((t_cb_button) {
		.pos = (t_pix) {list.pos.x + list.size.x - 40, list.pos.y},
		.size = (t_pix) {40, 40}, 
		.background = list.bg,
		.events = list.events,
		.callback = &self_add,
		.img = parse_tga("./textures/ui/plus.tga"),
		.scancode = SDL_SCANCODE_UNKNOWN,
	}, sdl);
	apush(&childs, &current);
	return (childs);
}

static t_list_state	*init_state(t_list_state *state, t_list_comp list, t_sdl *sdl)
{
	state->build = list.build;
	state->select = list.select;
	state->add = list.add;
	state->del = list.del;
	state->need_update = 1;
	state->bg = list.bg;
	state->events = list.events;
	state->sdl = sdl;
	state->y_scroll = 0;
	return (state);
}

t_component			init_list_comp(t_list_comp list, t_sdl *sdl)
{
	t_component		ret;
	t_list_state	*state;

	state = (t_list_state *)safe_malloc(sizeof(t_list_state), "components");
	ret = default_component(state, list.size, sdl);
	ret.update = &self_update;
	ret.render = &self_render;
	ret.pos = list.pos;
	ret.state = init_state(state, list, sdl);
	if (list.title)
		ret.text = component_text(list.title, (t_pix) {5, 5}, sdl);
	ret.childs = init_childs(list, sdl);
	return (ret);
}