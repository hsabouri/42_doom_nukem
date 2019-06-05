/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_button.2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 11:41:46 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/27 12:06:55 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./list_comp.h"

void				render_list_button(const t_component self, t_color *buf)
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

static void			init_update(t_component *self, t_list_state *list_state,
t_list_button_state *state)
{
	state->parent = list_state->parent;
	state->list = list_state;
	self->pos.y = state->d_pos.y - *state->y_scroll;
}

static int			relaxed(t_list_state *list_state,
t_list_button_state *state)
{
	list_state->need_update = state->select(list_state->parent, state->i);
	state->is_active = 0;
	return (1);
}

int					update_list_button(t_component *self, void *parent)
{
	t_list_state		*list_state;
	t_list_button_state	*state;
	int					ret;
	int					clicked;

	ret = 0;
	state = (t_list_button_state *)self->state;
	list_state = (t_list_state *)parent;
	init_update(self, list_state, state);
	if (self->childs.len)
		((t_component *)self->childs.first)->pos.y = state->d_pos.y
		- *state->y_scroll + 1;
	clicked = is_clicked_on(*self, *state->events);
	if (clicked && state->is_active == 0 && state->select)
	{
		state->is_active = 1;
		ret = 1;
	}
	if (!clicked && state->is_active && state->select)
		ret = relaxed(list_state, state);
	if (!clicked && state->events->any)
		ret = 1;
	return (ret);
}
