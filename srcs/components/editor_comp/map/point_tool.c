/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:46:47 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 14:30:52 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"

static t_game	self_update_selected(t_point_tool *state,
const t_editor_map_state *parent_state, t_event events, t_game game)
{
	if (*state->selected_point >= 0 && state->events->mouse[SDL_BUTTON_LEFT]
		&& (size_t)*state->selected_point < parent_state->env->game.npoints)
		game.points[*state->selected_point] = point_from_mouse(*parent_state,
			*state->events, parent_state->magnetisme);
	else if (*state->selected_point >= 0 && events.mouse_click[SDL_BUTTON_RIGHT]
		&& game.nuwalls == 0)
		game = delete_point(*state->selected_point, game);
	else if (*state->selected_point < 0 && events.mouse_click[SDL_BUTTON_RIGHT])
		game = create_point(point_from_mouse(*parent_state, events,
			parent_state->magnetisme), -1, game);
	return (game);
}

static int		self_update(t_component *self, void *parent)
{
	t_point_tool				*state;
	const t_editor_map_state	*parent_state = (t_editor_map_state *)parent;
	t_event						events;
	t_game						game;

	state = (t_point_tool *)self->state;
	events = *state->events;
	game = parent_state->env->game;
	if (parent_state->tool != CREATE_POINT)
	{
		self->display = 0;
		return (0);
	}
	else
		self->display = 1;
	*state->selected_point = select_point(*parent_state, *state->selected_point,
		events);
	parent_state->env->game = self_update_selected(state, parent_state,
		events, game);
	return (1);
}

t_component		init_point_tool(t_env *env, ssize_t *selected, t_sdl *sdl)
{
	t_component		ret;
	t_point_tool	*state;

	state = (t_point_tool *)safe_malloc(sizeof(t_point_tool), "component");
	ret = default_component(state, (t_pix) {0, 0}, sdl);
	state->events = &env->events;
	state->selected_point = selected;
	ret.update = &self_update;
	ret.complete_render = &empty_render;
	ret.childs = anew(NULL, 0, 0);
	return (ret);
}
