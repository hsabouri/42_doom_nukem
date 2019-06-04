/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:35:58 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 10:38:03 by hsabouri         ###   ########.fr       */
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

static t_array				init_childs(t_env *env, t_editor_map_state *state,
t_sdl *sdl)
{
	t_array		ret;
	t_component	current;

	ret = safe_anew(NULL, 10, sizeof(t_component), "commponents");
	current = init_button((t_button) {
		.pos = (t_pix) {2, 2},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &env->events,
		.img = parse_tga("./textures/ui/create_point.tga", 0),
		.to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_P,
		.active_value = CREATE_POINT}, sdl);
	apush(&ret, &current);
	current = init_button((t_button) {
		.pos = (t_pix) {44, 2},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &env->events,
		.img = parse_tga("./textures/ui/create_wall.tga", 0),
		.to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_O,
		.active_value = CREATE_WALL}, sdl);
	apush(&ret, &current);
	current = init_button((t_button) {
		.pos = (t_pix) {86, 2},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &env->events,
		.img = parse_tga("./textures/ui/assign_wall.tga", 0),
		.to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_L,
		.active_value = ASSIGN_WALL}, sdl);
	apush(&ret, &current);
	current = init_button((t_button) {
		.pos = (t_pix) {128, 2},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &env->events,
		.img = parse_tga("./textures/ui/create_portal.tga", 0),
		.to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_I,
		.active_value = CREATE_PORTAL}, sdl);
	apush(&ret, &current);
	current = init_button((t_button) {
		.pos = (t_pix) {172, 2},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &env->events,
		.img = parse_tga("./textures/ui/entity_tool.tga", 0),
		.to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_U,
		.active_value = TOOL_ENTITY}, sdl);
	apush(&ret, &current);
	current = init_button((t_button) {
		.pos = (t_pix) {214, 2},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &env->events,
		.img = parse_tga("./textures/ui/assign_entity.tga", 0),
		.to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_J,
		.active_value = ASSIGN_ENTITY}, sdl);
	apush(&ret, &current);
	current = init_button((t_button) {
		.pos = (t_pix) {258, 2},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &env->events,
		.img = parse_tga("./textures/ui/sector_color.tga", 0),
		.to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_Y,
		.active_value = SECTOR_COLOR}, sdl);
	apush(&ret, &current);
	current = init_point_tool(env, &state->selected_point, sdl);
	apush(&ret, &current);
	current = init_wall_tool(env, state, sdl);
	apush(&ret, &current);
	current = init_assign_tool(env, state, sdl);
	apush(&ret, &current);
	current = init_assign_portal_tool(env, state, sdl);
	apush(&ret, &current);
	current = init_sector_color_tool(env, state, sdl);
	apush(&ret, &current);
	current = init_display_deco((t_display_deco_state) {
		.to_look_at = (int *)&state->tool,
		.display_value = TOOL_ENTITY,
		.state = state,
		.invert = 0
	}, create_list_class(env, sdl));
	apush(&ret, &current);
	current = init_entity_tool(env, state, sdl);
	apush(&ret, &current);
	current = init_assign_entity(env, (t_assign_entity) {
		&state->selected_entity,
		&state->selected_spawn,
		&state->selected_wall,
		state->selected_walls,
		&state->entity,
		&state->spawn,
		&env->events
	}, sdl);
	apush(&ret, &current);
	current = init_sw_button((t_sw_button) {
		.pos = (t_pix) {302, 2},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &env->events,
		.img = parse_tga("./textures/ui/magnetisme.tga", 0),
		.to_activate = (int *)&state->magnetisme,
		.scancode = SDL_SCANCODE_LCTRL,
		.enable_value = 1,
		.disable_value = 0}, sdl);
	apush(&ret, &current);
	current = init_cb_button((t_cb_button) {
		.pos = (t_pix) {344, 2},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &env->events,
		.img = parse_tga("./textures/ui/grid_size.tga", 0),
		.callback = &grid_size,
		.scancode = SDL_SCANCODE_SPACE}, sdl);
	apush(&ret, &current);
	current = init_display_deco((t_display_deco_state) {
		.to_look_at = (int *)&env->events.keys[SDL_SCANCODE_H],
		.display_value = 1,
		.state = state,
		.invert = 0
	}, init_help_component((t_help_state) {
			.img = parse_tga("./textures/hud/map_editor.tga", 0)}, sdl));
	apush(&ret, &current);
	return (ret);
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
	ret.childs = init_childs(env, ret.state, sdl);
	return (ret);
}
