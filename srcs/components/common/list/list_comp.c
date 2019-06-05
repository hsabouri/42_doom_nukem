/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_comp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:36:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/28 12:03:55 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./list_comp.h"

static int			self_update(t_component *self, void *parent)
{
	t_list_state	*state;
	int				ret;

	ret = 0;
	state = (t_list_state *)self->state;
	state->parent = parent;
	if (is_over(*self, *state->events)
		&& (state->y_scroll > 0 || state->events->wheel > 0))
		state->y_scroll += state->events->wheel * 100;
	if (state->need_update
		|| (state->extern_need_update && *state->extern_need_update))
	{
		self->childs = build_childs(self, state, parent, state->sdl);
		state->need_update = 0;
		if (state->extern_need_update)
			*state->extern_need_update = 0;
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

static t_list_state	*init_state(t_list_state *state, t_list_comp list,
t_sdl *sdl)
{
	state->build = list.build;
	state->select = list.select;
	state->add = list.add;
	state->del = list.del;
	state->need_update = 1;
	state->extern_need_update = list.extern_need_update;
	state->bg = list.bg;
	state->events = list.events;
	state->sdl = sdl;
	state->y_scroll = 0;
	state->destroy_image = list.destroy_image;
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
	ret.childs = list_init_childs(list, sdl);
	return (ret);
}
