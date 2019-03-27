/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:46:47 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/27 16:45:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"

static ssize_t	select_point(t_editor_map_state editor, t_point_tool state,
t_event events)
{
	const t_game	game = editor.env->game;
	float	min;
	ssize_t	min_id;
	size_t	i;
	float	current;

	if (events.mouse[SDL_BUTTON_LEFT] && *state.selected_point >= 0)
		return (*state.selected_point);
	i = 0;
	min = 20 / editor.zoom;
	min_id = -1;
	while (i < game.npoints)
	{
		current = circle(game.points[i], point_from_mouse(editor, events, 0));
		if (current < min + 0.0001)
		{
			min = current;
			min_id = (ssize_t)i;
		}
		i++;
	}
	return (min_id);
}

static int		self_update(t_component *self, void *parent)
{
	t_point_tool				*state;
	const t_editor_map_state 	*parent_state = (t_editor_map_state *)parent;
	t_event						events;
	t_game						game;

	state = (t_point_tool *)self->state;
	events = *state->events;
	game = parent_state->env->game;
	if (parent_state->tool != CREATE_POINT)
	{
		self->display = 0;
		return (1);
	}
	*state->selected_point = select_point(*parent_state, *state, events);
	if (state->selected_point >= 0 && state->events->mouse[SDL_BUTTON_LEFT] &&
		(size_t)*state->selected_point < parent_state->env->game.npoints)
		game.points[*state->selected_point] = point_from_mouse(*parent_state,
			*state->events, parent_state->magnetisme);
	else if (*state->selected_point >= 0 && events.mouse_click[SDL_BUTTON_RIGHT])
		game = delete_point(*state->selected_point, game);
	else if (*state->selected_point < 0 && events.mouse_click[SDL_BUTTON_RIGHT])
		game = create_point(point_from_mouse(*parent_state, events,
			parent_state->magnetisme), -1, game);
	parent_state->env->game = game;
	return (1);
}

t_component		init_point_tool(t_env *env, ssize_t *selected, t_sdl *sdl)
{
	t_component		ret;
	t_point_tool	*state;

	state = (t_point_tool *)malloc(sizeof(t_point_tool));
	ret = default_component(state, (t_pix) {0, 0}, sdl);
	state->events = &env->events;
	state->selected_point = selected;
	ret.update = &self_update;
	ret.complete_render = &empty_render;
	ret.childs = anew(NULL, 0, 0);
	return (ret);
}