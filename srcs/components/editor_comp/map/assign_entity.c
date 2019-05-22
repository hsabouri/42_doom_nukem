/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:47:39 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/22 17:22:52 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"

static t_assign_entity	select_entity_wall(t_assign_entity state,
t_event events)
{
	if (events.mouse_click[SDL_BUTTON_LEFT])
	{
		if (*state.selected_entity >= 0)
		{
			*state.entity = *state.selected_entity;
			*state.spawn = -1;
		}
		else if (*state.selected_spawn >= 0)
		{
			*state.spawn = *state.selected_spawn;
			*state.entity = -1;
		}
		else if (*state.selected_wall && events.mouse_click[SDL_BUTTON_LEFT] &&
			(*state.entity >= 0 || *state.spawn >= 0))
			state.walls[1] = *state.selected_wall;
		else
		{
			*state.spawn = -1;
			*state.entity = -1;
			state.walls[1] = -1;
		}
	}
	return (state);
}

static t_game			assign_entity(t_assign_entity *state, t_game game)
{
	const size_t	sector = find_sector(state->walls[1], game);

	if ((size_t)*state->entity == game.nentities)
		game.player.my_entity.physic.sector_id = sector;
	else if ((size_t)*state->spawn == game.nentities)
		game.player.my_entity.spawn.sector_id = sector;
	else if (*state->entity >= 0)
		game.entities[*state->entity].physic.sector_id = sector;
	else if (*state->spawn >= 0)
		game.entities[*state->spawn].spawn.sector_id = sector;
	*state->entity = -1;
	*state->spawn = -1;
	state->walls[1] = -1;
	*state->selected_entity = -1;
	*state->selected_spawn = -1;
	*state->selected_wall = -1;
	return (game);
}

static int				self_update(t_component *self, void *parent)
{
	t_assign_entity				*state;
	const t_editor_map_state 	*parent_state = (t_editor_map_state *)parent;
	t_event						events;
	t_game						game;

	state = (t_assign_entity *)self->state;
	events = *state->events;
	game = parent_state->env->game;
	if (parent_state->tool != ASSIGN_ENTITY)
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
	if (*state->entity >= 0 || *state->spawn >= 0)
		*state->selected_wall = select_wall(*parent_state,
			*state->selected_wall, events);
	*state = select_entity_wall(*state, events);
	if (*state->entity >= 0 && state->walls[1] >= 0)
		game = assign_entity(state, game);
	parent_state->env->game = game;
	return (1);
}

t_component				init_assign_entity(t_env *env, t_assign_entity v,
t_sdl *sdl)
{
	t_component		ret;
	t_assign_entity	*state;

	(void)env;
	state = (t_assign_entity *)safe_malloc(sizeof(t_assign_entity), "component");
	*state = v;
	ret = default_component(state, (t_pix) {0, 0}, sdl);
	ret.update = &self_update;
	ret.complete_render = &empty_render;
	ret.childs = anew(NULL, 0, 0);
	return (ret);
}
