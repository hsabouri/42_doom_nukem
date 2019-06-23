/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:45:12 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/23 15:23:14 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./materials.h"
#include "../../common/common.h"

static t_array	init_child_3(t_env *env, t_editor_mat_state *state,
t_sdl *sdl, t_array ret)
{
	t_component	current;

	current = init_cb_button((t_cb_button) {.place_holder = "LINK OVERLAY",
		.pos = (t_pix) {204, 404},
		.background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events, .callback = &enable_change_overlay
		}, sdl);
	apush(&ret, &current);
	current = create_list_textures(env, (t_pix) {WIDTH - 167, 44},
		(t_pix) {165, HEIGHT - 54}, sdl);
	apush(&ret, &current);
	current = init_display_deco((t_display_deco_state) {.display_value = 1,
		.to_look_at = &state->display_overlay, .state = state},
		init_simple_rectangle((t_pix) {0, 0}, (t_pix) {WIDTH, HEIGHT},
		(t_color) {0, 0, 0, 128}, sdl));
	apush(&ret, &current);
	current = init_display_deco((t_display_deco_state) {.display_value = 1,
		.to_look_at = &state->display_overlay, .state = state},
		create_list_overlay(env, &state->update_overlay, sdl));
	apush(&ret, &current);
	return (ret);
}

t_array			init_child_2(t_env *env, t_editor_mat_state *state,
t_sdl *sdl, t_array ret)
{
	t_component	current;

	current = init_button_ft((t_button_ft) {.pos = (t_pix) {204, 369},
		.background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events, .place_holder = "TILING",
		.to_activate = (int **)&state->selected_mode,
		.scancode = SDL_SCANCODE_UNKNOWN, .active_value = TILING}, sdl);
	apush(&ret, &current);
	current = init_button_ft((t_button_ft) {.place_holder = "NO TILING",
		.pos = (t_pix) {current.pos.x + current.size.x + 2, 369},
		.background = (t_color) {70, 70, 70, 255}, .active_value = NO_TILING,
		.events = &state->env->events, .scancode = SDL_SCANCODE_UNKNOWN,
		.to_activate = (int **)&state->selected_mode}, sdl);
	apush(&ret, &current);
	current = init_button_ft((t_button_ft) {.place_holder = "SKYBOX",
		.pos = (t_pix) {current.pos.x + current.size.x + 2, 369},
		.background = (t_color) {70, 70, 70, 255}, .active_value = SKYBOX,
		.events = &state->env->events, .scancode = SDL_SCANCODE_UNKNOWN,
		.to_activate = (int **)&state->selected_mode}, sdl);
	apush(&ret, &current);
	ret = init_child_3(env, state, sdl, ret);
	return (ret);
}
