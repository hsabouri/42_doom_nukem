/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:35:58 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/19 11:58:03 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common/common.h"
#include "./map.h"

static t_editor_map_state	*init_state(t_editor_map_state *state, t_env *env)
{
	state->env = env;
	state->offset = vec2_new(INITIAL_OFFSET_X, INITIAL_OFFSET_Y);
	state->zoom = INITIAL_ZOOM;
	state->grid_size = 1;
	state->magnetisme = 1;
	state->tool = MOVE;
	state->selected_point = -1;
	state->selected_wall = -1;
	state->unassigned_wall = -1;
	state->wall_points[0] = -1;
	state->wall_points[1] = -1;
	state->selected_walls[0] = -1;
	state->selected_walls[1] = -1;
	state->selected_entity = -1;
	state->entity = -1;
	state->spawn = -1;
	state->selected_class = -1;
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
	ret.state = init_state((t_editor_map_state *)safe_malloc(
		sizeof(t_editor_map_state), "components"), env);
	ret.update = &map_editor_update;
	ret.destroy = NULL;
	ret.render = &map_editor_render;
	ret.complete_render = NULL;
	ret.last_render = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	ret.childs = index_childs_1(env, ret.state, sdl);
	ret.childs = index_childs_2(env, ret.state, sdl, ret.childs);
	ret.childs = index_childs_3(env, ret.state, sdl, ret.childs);
	ret.childs = index_childs_4(env, ret.state, sdl, ret.childs);
	ret.childs = index_childs_5(env, ret.state, sdl, ret.childs);
	return (ret);
}
