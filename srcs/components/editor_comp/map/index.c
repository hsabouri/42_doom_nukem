/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:35:58 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/24 17:27:27 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"

static t_editor_map_state	zoom_move(t_editor_map_state state, t_event events)
{
	state.offset.u -= events.keys[SDL_SCANCODE_D] * MOVE_SPEED;
	state.offset.u += events.keys[SDL_SCANCODE_A] * MOVE_SPEED;
	state.offset.v -= events.keys[SDL_SCANCODE_S] * MOVE_SPEED;
	state.offset.v += events.keys[SDL_SCANCODE_W] * MOVE_SPEED;
	state.zoom *= 1 + ZOOM_SPEED * events.wheel;
	if (state.zoom <= 0.1)
		state.zoom = 0.1;
	return (state);
}

static void					self_render(const t_component self, t_color *buf)
{
	const t_editor_map_state	state = *(t_editor_map_state *)self.state;

	background(buf, RICH_BLACK, self.size);
	draw_map(state, buf);
}

static int					self_update(t_component *self, void *parent)
{
	t_editor_root_state		*parent_state;
	t_editor_map_state		*state;
	static t_editor_type	last = MAP;

	parent_state = (t_editor_root_state *)parent;
	state = (t_editor_map_state *)self->state;
	if (parent_state->type != MAP)
	{
		last = parent_state->type;
		self->display = 0;
		return (0);
	}
	else if (parent_state->type == MAP)
	{
		*state = zoom_move(*state, parent_state->env->events);
		if (last != MAP)
		{
			last = MAP;
			self->display = 1;
			return (1);
		}
		if (parent_state->env->events.any)
			return (1);
		return (0);
	}
	else 
	return (0);
}

static t_editor_map_state	*init_state(t_editor_map_state *state, t_env *env)
{
	state->game = &env->game;
	state->unassigned_walls = anew(NULL, 5, sizeof(t_wall));
	apush(&state->unassigned_walls, &env->game.walls[0]);
	apush(&state->unassigned_walls, &env->game.walls[1]);
	apush(&state->unassigned_walls, &env->game.walls[2]);
	apush(&state->unassigned_walls, &env->game.walls[3]);
	apush(&state->unassigned_walls, &env->game.walls[4]);
	state->offset = vec2_new(INITIAL_OFFSET_X, INITIAL_OFFSET_Y);
	state->zoom = INITIAL_ZOOM;
	state->grid_size = 1;
	return (state);
}

t_component					init_editor_map(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret.img.content = NULL;
	ret.text.text_texture = NULL;
	ret.size.x = WIDTH;
	ret.size.y = HEIGHT;
	ret.pos.x = 0;
	ret.pos.y = 0;
	ret.display = 1;
	ret.state = init_state((t_editor_map_state *)malloc(
		sizeof(t_editor_map_state)), env);
	ret.update = &self_update;
	ret.destroy = NULL;
	ret.render = &self_render;
	ret.complete_render = NULL;
	ret.last_render = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	ret.childs = anew(NULL, 0, 1);
	return (ret);
}