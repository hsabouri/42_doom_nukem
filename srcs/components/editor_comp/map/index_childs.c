/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 13:45:59 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 13:48:25 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"
#include "../../common/common.h"

t_array	index_childs_1(t_env *env, t_editor_map_state *state, t_sdl *sdl)
{
	t_component	current;
	t_array		ret;

	ret = safe_anew(NULL, 10, sizeof(t_component), "commponents");
	current = init_button((t_button) { .pos = (t_pix) {2, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.img = parse_tga("./textures/ui/create_point.tga", 0),
		.to_activate = (int *)&state->tool, .events = &env->events,
		.scancode = SDL_SCANCODE_P, .active_value = CREATE_POINT}, sdl);
	apush(&ret, &current);
	current = init_button((t_button) { .pos = (t_pix) {44, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.img = parse_tga("./textures/ui/create_wall.tga", 0),
		.events = &env->events, .to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_O, .active_value = CREATE_WALL}, sdl);
	apush(&ret, &current);
	current = init_button((t_button) { .pos = (t_pix) {86, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.img = parse_tga("./textures/ui/assign_wall.tga", 0),
		.to_activate = (int *)&state->tool, .events = &env->events,
		.scancode = SDL_SCANCODE_L, .active_value = ASSIGN_WALL}, sdl);
	apush(&ret, &current);
	current = init_point_tool(env, &state->selected_point, sdl);
	apush(&ret, &current);
	return (ret);
}

t_array	index_childs_2(t_env *env, t_editor_map_state *state,
t_sdl *sdl, t_array ret)
{
	t_component	current;

	current = init_button((t_button) { .pos = (t_pix) {128, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.img = parse_tga("./textures/ui/create_portal.tga", 0),
		.to_activate = (int *)&state->tool, .events = &env->events,
		.scancode = SDL_SCANCODE_I, .active_value = CREATE_PORTAL}, sdl);
	apush(&ret, &current);
	current = init_button((t_button) { .pos = (t_pix) {172, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.img = parse_tga("./textures/ui/entity_tool.tga", 0),
		.events = &env->events, .to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_U, .active_value = TOOL_ENTITY}, sdl);
	apush(&ret, &current);
	current = init_button((t_button) { .pos = (t_pix) {214, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.img = parse_tga("./textures/ui/assign_entity.tga", 0),
		.events = &env->events, .to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_J, .active_value = ASSIGN_ENTITY}, sdl);
	apush(&ret, &current);
	current = init_wall_tool(env, state, sdl);
	apush(&ret, &current);
	current = init_assign_tool(env, state, sdl);
	apush(&ret, &current);
	return (ret);
}

t_array	index_childs_3(t_env *env, t_editor_map_state *state,
t_sdl *sdl, t_array ret)
{
	t_component	current;

	current = init_button((t_button) { .pos = (t_pix) {258, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.img = parse_tga("./textures/ui/sector_color.tga", 0),
		.events = &env->events, .to_activate = (int *)&state->tool,
		.scancode = SDL_SCANCODE_Y, .active_value = SECTOR_COLOR}, sdl);
	apush(&ret, &current);
	current = init_assign_portal_tool(env, state, sdl);
	apush(&ret, &current);
	current = init_sector_color_tool(env, state, sdl);
	apush(&ret, &current);
	current = init_display_deco((t_display_deco_state) {
		.to_look_at = (int *)&state->tool, .display_value = TOOL_ENTITY,
		.state = state, .invert = 0 }, create_list_class(env, sdl));
	apush(&ret, &current);
	current = init_entity_tool(env, state, sdl);
	apush(&ret, &current);
	current = init_assign_entity(env, (t_assign_entity) {
		&state->selected_entity, &state->selected_spawn,
		&state->selected_wall, state->selected_walls,
		&state->entity, &state->spawn, &env->events }, sdl);
	apush(&ret, &current);
	return (ret);
}

t_array	index_childs_4(t_env *env, t_editor_map_state *state,
t_sdl *sdl, t_array ret)
{
	t_component	current;

	current = init_sw_button((t_sw_button) { .pos = (t_pix) {302, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.img = parse_tga("./textures/ui/magnetisme.tga", 0), .enable_value = 1,
		.events = &env->events, .to_activate = (int *)&state->magnetisme,
		.scancode = SDL_SCANCODE_LCTRL, .disable_value = 0}, sdl);
	apush(&ret, &current);
	current = init_cb_button((t_cb_button) { .pos = (t_pix) {344, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.img = parse_tga("./textures/ui/grid_size.tga", 0),
		.events = &env->events, .callback = &grid_size,
		.scancode = SDL_SCANCODE_SPACE}, sdl);
	apush(&ret, &current);
	current = init_display_deco((t_display_deco_state) { .display_value = 1,
		.to_look_at = (int *)&env->events.keys[SDL_SCANCODE_H],
		.state = state, .invert = 0 }, init_help_component((t_help_state) {
			.img = parse_tga("./textures/hud/map_editor.tga", 0)}, sdl));
	apush(&ret, &current);
	return (ret);
}
