/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:50:54 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/02 10:30:54 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"

static t_game	move_entity(const t_editor_map_state *parent_state,
t_entity_tool *state, t_game game)
{
	const t_vec2	pos = point_from_mouse(*parent_state, *state->events,
		parent_state->magnetisme);
	t_vec3			*to_change;
	
	if (*state->selected_entity >= 0)
	{
		if ((size_t)*state->selected_entity == game.nentities)
			to_change = &game.player.my_entity.physic.pos;
		else
			to_change = &game.entities[*state->selected_entity].physic.pos;
	}
	else
	{
		if ((size_t)*state->selected_spawn == game.nentities)
			to_change = &game.player.my_entity.spawn.pos;
		else
			to_change = &game.entities[*state->selected_spawn].spawn.pos;
	}
	to_change->x = pos.u;
	to_change->y = pos.v;
	return (game);
}

static int		self_update(t_component *self, void *parent)
{
	t_entity_tool				*state;
	const t_editor_map_state 	*parent_state = (t_editor_map_state *)parent;
	t_event						events;
	t_game						game;

	state = (t_entity_tool *)self->state;
	events = *state->events;
	game = parent_state->env->game;
	if (parent_state->tool != TOOL_ENTITY)
	{
		self->display = 0;
		return (0);
	}
	else
		self->display = 1;
	*state->selected_entity = select_entity(*parent_state,
		*state->selected_entity, events, 0);
	if (*state->selected_entity == -1)
		*state->selected_spawn = select_entity(*parent_state,
			*state->selected_spawn, events, 1);
	if ((*state->selected_entity >= 0 || *state->selected_spawn >= 0) &&
		state->events->mouse[SDL_BUTTON_LEFT])
		game = move_entity(parent_state, state, game);
	else if (*state->selected_entity > -1 && events.mouse_click[SDL_BUTTON_RIGHT])
		game = delete_entity(*state->selected_entity, game);
	parent_state->env->game = game;
	return (1);
}

t_component		init_entity_tool(t_env *env, ssize_t *entity,
ssize_t *spawn, t_sdl *sdl)
{
	t_component		ret;
	t_entity_tool	*state;

	state = (t_entity_tool *)safe_malloc(sizeof(t_entity_tool), "component");
	ret = default_component(state, (t_pix) {0, 0}, sdl);
	state->events = &env->events;
	state->selected_entity = entity;
	state->selected_spawn = spawn;
	ret.update = &self_update;
	ret.complete_render = &empty_render;
	ret.childs = anew(NULL, 0, 0);
	return (ret);
}
