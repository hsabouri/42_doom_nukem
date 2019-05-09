/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/09 11:32:21 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./materials.h"
#include "../../common/common.h"

static void					self_render(const t_component self, t_color *buf)
{
	const t_editor_mat_state	state = *(t_editor_mat_state *)self.state;

	background(buf, RICH_BLACK, self.size);
}

static int					self_update(t_component *self, void *parent)
{
	t_editor_mat_state		*state;

	state = (t_editor_mat_state *)self->state;
	(void)parent;
	if (state->env->events.any)
		return (1);
	return (0);
}

static t_editor_mat_state	*init_state(t_editor_mat_state *state, t_env *env)
{
	state->env = env;
	state->selected = 0;
	state->selected_color = &env->game.materials[state->selected].color;
	state->selected_filter = &env->game.materials[state->selected].filter;
	state->selected_mode = &env->game.materials[state->selected].mode;
	return (state);
}

static t_array				init_childs(t_env *env, t_editor_mat_state *state,
t_sdl *sdl)
{
	t_array		ret;
	t_component	current;

	ret = safe_anew(NULL, 1, sizeof(t_component), "commponents");
	current = create_list_materials(env, sdl);
	apush(&ret, &current);
	current = init_simple_text("PREVIEW", (t_pix) {206, 3}, sdl);
	apush(&ret, &current);
	current = init_preview(state, (t_pix) {204, 30}, sdl);
	apush(&ret, &current);
	current = init_simple_text("COLOR", (t_pix) {507, 3}, sdl);
	apush(&ret, &current);
	current = init_color_chooser(&state->selected_color,
		(t_pix) {505, 29}, sdl);
	apush(&ret, &current);
	current = init_simple_text("FILTER", (t_pix) {810, 3}, sdl);
	apush(&ret, &current);
	current = init_color_chooser(&state->selected_filter,
		(t_pix) {808, 29}, sdl);
	apush(&ret, &current);
	current = init_simple_text("TEXTURE MODE", (t_pix) {204, 343}, sdl);
	apush(&ret, &current);
	current = init_button_ft((t_button_ft) {
		.pos = (t_pix) {204, 369},
		.background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events,
		.place_holder = "TILING",
		.to_activate = (int **)&state->selected_mode,
		.scancode = SDL_SCANCODE_UNKNOWN,
		.active_value = TILING}, sdl);
	apush(&ret, &current);
	current = init_button_ft((t_button_ft) {
		.pos = (t_pix) {current.pos.x + current.size.x + 2, 369},
		.background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events,
		.place_holder = "NO TILING",
		.to_activate = (int **)&state->selected_mode,
		.scancode = SDL_SCANCODE_UNKNOWN,
		.active_value = NO_TILING}, sdl);
	apush(&ret, &current);
	current = init_button_ft((t_button_ft) {
		.pos = (t_pix) {current.pos.x + current.size.x + 2, 369},
		.background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events,
		.place_holder = "SKYBOX",
		.to_activate = (int **)&state->selected_mode,
		.scancode = SDL_SCANCODE_UNKNOWN,
		.active_value = SKYBOX}, sdl);
	apush(&ret, &current);
	current = create_list_textures(env, (t_pix) {WIDTH - 167, 2}, (t_pix) {165, HEIGHT - 4}, sdl);
	apush(&ret, &current);
	return (ret);
}

t_component					init_editor_mat(t_env *env, t_sdl *sdl)
{
	t_component			ret;
	t_editor_mat_state	*state;

	state = (t_editor_mat_state *)safe_malloc(sizeof(t_editor_mat_state), "components");
	ret = default_component(state, (t_pix) {WIDTH, HEIGHT}, sdl);
	ret.state = init_state(ret.state, env);
	ret.pos.x = 0;
	ret.pos.y = 0;
	ret.display = 1;
	ret.update = &self_update;
	ret.destroy = NULL;
	ret.render = &self_render;
	ret.complete_render = NULL;
	ret.childs = init_childs(env, ret.state, sdl);
	return (ret);
}
