/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_portal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:42:38 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/12 17:08:02 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"

static void		select_multi_portal(ssize_t wall, ssize_t *dual, t_event events)
{
	if (events.mouse_click[SDL_BUTTON_LEFT])
	{
		if (wall >= 0 && wall != dual[0])
			dual[0] = wall;
		else
			dual[0] = -1;
	}
	else if (events.mouse_click[SDL_BUTTON_RIGHT])
	{
		if (wall >= 0 && wall != dual[1])
			dual[1] = wall;
		else
			dual[1] = -1;
	}
}

static int		self_update(t_component *self, void *parent)
{
	t_assign_portal_tool		*state;
	t_event						events;

	state = (t_assign_portal_tool *)self->state;
	state->parent = (t_editor_map_state *)parent;
	events = *state->events;
	if (state->parent->tool != CREATE_PORTAL)
	{
		self->display = 0;
		return (0);
	}
	else
		self->display = 1;
	*state->selected_wall = select_wall(*state->parent,
		*state->selected_wall, events);
	select_multi_portal(*state->selected_wall, state->walls, *state->events);
	if (state->walls[0] >= 0 && state->walls[1] >= 0)
	{
		if (state->walls[0] != state->walls[1])
			state->parent->env->game = create_portal(state->walls[0],
				state->walls[1], state->parent->env->game);
		state->walls[0] = -1;
		state->walls[1] = -1;
	}
	return (1);
}

t_component		init_assign_portal_tool(t_env *env, t_editor_map_state *parent,
t_sdl *sdl)
{
	t_component				ret;
	t_component				child;
	t_assign_portal_tool	*state;

	state = (t_assign_portal_tool *)safe_malloc(sizeof(t_assign_portal_tool),
		"component");
	ret = default_component(state, (t_pix) {0, 0}, sdl);
	state->events = &env->events;
	state->selected_wall = &parent->selected_wall;
	state->walls = (ssize_t *)&parent->selected_walls;
	ret.update = &self_update;
	ret.complete_render = &empty_render;
	ret.childs = anew(NULL, 0, sizeof(t_component));
	return (ret);
}