/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_color_tool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:29:40 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 14:32:04 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"
#include "../materials/materials.h"

static int		self_update(t_component *self, void *parent)
{
	t_sector_color_tool			*state;
	const t_editor_map_state	*parent_state = (t_editor_map_state *)parent;
	t_event						events;
	t_game						game;

	state = (t_sector_color_tool *)self->state;
	events = *state->events;
	game = parent_state->env->game;
	if (parent_state->tool != SECTOR_COLOR)
	{
		self->display = 0;
		return (0);
	}
	else
		self->display = 1;
	*state->selected_wall = select_wall(*parent_state, *state->selected_wall,
		events);
	if (*state->selected_wall >= 0 && events.mouse_click[SDL_BUTTON_LEFT])
		state->sector = find_sector((size_t)*state->selected_wall, game);
	if (state->sector >= 0)
		state->color = &game.sectors[state->sector].ambient;
	parent_state->env->game = game;
	return (1);
}

t_component		init_sector_color_tool(t_env *env, t_editor_map_state *parent,
t_sdl *sdl)
{
	t_component			ret;
	t_sector_color_tool	*state;
	t_component			child;

	state = (t_sector_color_tool *)safe_malloc(sizeof(t_sector_color_tool),
		"component");
	ret = default_component(state, (t_pix) {0, 0}, sdl);
	state->env = env;
	state->events = &env->events;
	state->selected_wall = &parent->selected_wall;
	state->sector = -1;
	state->color = NULL;
	ret.update = &self_update;
	ret.complete_render = &empty_render;
	ret.childs = anew(NULL, 1, sizeof(t_component));
	child = init_color_chooser(&state->color, (t_pix) {WIDTH - 304, 44}, sdl);
	apush(&ret.childs, &child);
	return (ret);
}
