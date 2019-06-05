/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:34:13 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 14:40:39 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"

static t_game	delete_unassigned(size_t uwall, t_game game)
{
	game.walls = array_close(game.walls, game.nwalls + uwall,
		game.nwalls + game.nuwalls, sizeof(t_wall));
	game.nuwalls--;
	return (game);
}

static t_game	create_unassigned(ssize_t pts[2], t_game game)
{
	t_wall	new;

	new = (t_wall) {fvec2_new(0, 0), -1, MIN(pts[0], pts[1]),
		MAX(pts[0], pts[1]), game.materials, vec2_new(0, 0), vec2_new(0, 0)};
	game.walls = (t_wall *)safe_realloc(game.walls, sizeof(t_wall)
		* (game.nwalls + game.nuwalls + 1), "component");
	game.walls[game.nwalls + game.nuwalls] = new;
	game.nuwalls += 1;
	pts[0] = pts[1];
	pts[1] = -1;
	return (game);
}

static t_game	self_update_selected(t_wall_tool *state,
t_editor_map_state *parent_state, t_event events, t_game game)
{
	if (*state->selected_point == -1 && *state->unassigned_wall == -1)
		*state->selected_wall = select_wall(*parent_state,
			*state->selected_wall, events);
	else
		*state->selected_wall = -1;
	select_multi(*state->selected_point, state->wall_points, *state->events);
	if (state->wall_points[0] > -1 && state->wall_points[1] > -1)
		game = create_unassigned(state->wall_points, game);
	if (*state->selected_wall > -1 && events.mouse_click[SDL_BUTTON_RIGHT])
		game = delete_wall(*state->selected_wall, game);
	else if (*state->unassigned_wall > -1
		&& events.mouse_click[SDL_BUTTON_RIGHT])
		game = delete_unassigned(*state->unassigned_wall, game);
	return (game);
}

static int		self_update(t_component *self, void *parent)
{
	t_wall_tool			*state;
	t_editor_map_state	*parent_state;
	t_event				events;

	parent_state = (t_editor_map_state *)parent;
	state = (t_wall_tool *)self->state;
	events = *state->events;
	if (parent_state->tool != CREATE_WALL)
	{
		self->display = 0;
		return (0);
	}
	else
		self->display = 1;
	*state->selected_point = select_point(*parent_state, *state->selected_point,
		events);
	if (*state->selected_point == -1)
		*state->unassigned_wall = select_unassigned_wall(*parent_state,
			*state->unassigned_wall, events);
	else
		*state->unassigned_wall = -1;
	parent_state->env->game = self_update_selected(state, parent_state, events,
		parent_state->env->game);
	return (1);
}

t_component		init_wall_tool(t_env *env, t_editor_map_state *parent,
				t_sdl *sdl)
{
	t_component ret;
	t_wall_tool	*state;

	state = (t_wall_tool *)safe_malloc(sizeof(t_wall_tool), "component");
	ret = default_component(state, (t_pix) {0, 0}, sdl);
	state->events = &env->events;
	state->wall_points = (ssize_t *)parent->wall_points;
	state->selected_point = &parent->selected_point;
	state->selected_wall = &parent->selected_wall;
	state->unassigned_wall = &parent->unassigned_wall;
	ret.update = &self_update;
	ret.complete_render = &empty_render;
	ret.childs = anew(NULL, 0, 0);
	return (ret);
}
