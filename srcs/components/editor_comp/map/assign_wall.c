/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:43:54 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/12 13:26:31 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"
#include "../../common/common.h"

int			callback_new_sector(void *parent)
{
	t_assign_tool	*state;
	t_game			game;

	state = (t_assign_tool *)((t_display_deco_state *)parent)->state;
	game = state->parent->env->game;
	game = create_sector(game.nwalls, 0, game);
	game = create_wall(state->walls[0], game.nsectors - 1, game);
	state->walls[0] = -1;
	state->walls[1] = -1;
	state->parent->env->game = game;
	return (1);
}

void		select_multi_unassigned(ssize_t wall, ssize_t u_wall, ssize_t *dual,
t_event events)
{
	if (events.mouse_click[SDL_BUTTON_LEFT])
	{
		if (dual[0] >= 0 && dual[0] == u_wall)
			dual[0] = -1;
		else if (u_wall >= 0)
			dual[0] = u_wall;
		else if (wall >= 0)
			dual[1] = wall;
		else
			dual[1] = -1;
	}
}

static size_t	find_sector(size_t wall_id, t_game game)
{
	size_t	i;

	i = 0;
	while (i < game.nsectors - 1)
	{
		if (game.sectors[i].start <= wall_id &&
			game.sectors[i + 1].start > wall_id)
		return (i);
		++i;
	}
	return (game.nsectors - 1);
}

static int		self_update(t_component *self, void *parent)
{
	t_assign_tool				*state;
	t_event						events;

	state = (t_assign_tool *)self->state;
	state->parent = (t_editor_map_state *)parent;
	events = *state->events;
	if (state->parent->tool != ASSIGN_WALL)
	{
		self->display = 0;
		return (0);
	}
	else
		self->display = 1;
	*state->unassigned_wall = select_unassigned_wall(*state->parent,
			*state->unassigned_wall, events);
	if (state->walls[0] >= 0)
		*state->selected_wall = select_wall(*state->parent,
		*state->selected_wall, events);
	select_multi_unassigned(*state->selected_wall, *state->unassigned_wall,
		state->walls, *state->events);
	if (state->walls[0] >= 0 && state->walls[1] >= 0)
	{
		state->parent->env->game = create_wall(state->walls[0],
			find_sector(state->walls[1],
			state->parent->env->game), state->parent->env->game);
		state->walls[0] = -1;
		state->walls[1] = -1;
		*state->unassigned_wall = -1;
		*state->selected_wall = -1;
	}
	return (1);
}

t_component		init_assign_tool(t_env *env, t_editor_map_state *parent,
t_sdl *sdl)
{
	t_component		ret;
	t_component		child;
	t_assign_tool	*state;

	state = (t_assign_tool *)safe_malloc(sizeof(t_assign_tool), "component");
	ret = default_component(state, (t_pix) {0, 0}, sdl);
	state->events = &env->events;
	state->selected_wall = &parent->selected_wall;
	state->walls = (ssize_t *)&parent->selected_walls;
	state->unassigned_wall = &parent->unassigned_wall;
	ret.update = &self_update;
	ret.complete_render = &empty_render;
	ret.childs = anew(NULL, 1, sizeof(t_component));
	child = init_display_deco((t_display_deco_state) {
		(int *)state->walls, -1, state, 1
	}, init_cb_button((t_cb_button) {
		.pos = (t_pix) {2, 44},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &env->events,
		.scancode = SDL_SCANCODE_N,
		.place_holder = NULL,
		.callback = &callback_new_sector,
		.img = parse_tga("./textures/ui/plus.tga")
	}, sdl));
	apush(&ret.childs, &child);
	return (ret);
}