/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:19:07 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 10:32:20 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"

int							grid_size(void *map_state)
{
	t_editor_map_state *state;

	state = (t_editor_map_state *)map_state;
	if (state->grid_size * 2 > 8)
		state->grid_size = 0;
	else if (state->grid_size > 0)
		state->grid_size *= 2;
	else
		state->grid_size = 1;
	return (1);
}

static t_editor_map_state	zoom_move(t_editor_map_state state, t_event events)
{
	const float	factor = 1 + ZOOM_SPEED * events.wheel;

	state.offset.u -= events.keys[SDL_SCANCODE_D] * MOVE_SPEED;
	state.offset.u += events.keys[SDL_SCANCODE_A] * MOVE_SPEED;
	state.offset.v -= events.keys[SDL_SCANCODE_S] * MOVE_SPEED;
	state.offset.v += events.keys[SDL_SCANCODE_W] * MOVE_SPEED;
	state.zoom *= factor;
	if (state.zoom <= 0.1)
		state.zoom = 0.1;
	else
		state.offset = vec2_new(
			state.offset.u * factor - (events.x - WIDTH / 2) * (factor - 1),
			state.offset.v * factor - (events.y - HEIGHT / 2) * (factor - 1));
	return (state);
}

void						map_editor_render(const t_component self,
t_color *buf)
{
	const t_editor_map_state	state = *(t_editor_map_state *)self.state;

	background(buf, RICH_BLACK, self.size);
	draw_map(state, buf);
}

int							map_editor_update_state(t_editor_map_state *state,
t_editor_root_state *parent_state, t_editor_type *last, t_component *self)
{
	*state = zoom_move(*state, parent_state->env->events);
	if (*last != MAP)
	{
		*last = MAP;
		self->display = 1;
		return (1);
	}
	if (parent_state->env->events.any)
		return (1);
	return (0);
}

int							map_editor_update(t_component *self, void *parent)
{
	t_editor_root_state		*parent_state;
	t_editor_map_state		*state;
	static t_editor_type	last = MAP;

	parent_state = (t_editor_root_state *)parent;
	state = (t_editor_map_state *)self->state;
	state->env = parent_state->env;
	if (parent_state->type != MAP)
	{
		last = parent_state->type;
		self->display = 0;
		return (0);
	}
	else if (parent_state->type == MAP)
		return (map_editor_update_state(state, parent_state, &last, self));
	return (0);
}
