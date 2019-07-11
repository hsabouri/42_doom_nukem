/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:04:16 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/11 11:08:07 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../root.h"
#include "./editor_comp.h"
#include "./map/map.h"
#include "./materials/materials.h"
#include "../common/common.h"

static t_array				init_childs_2(t_editor_root_state *state,
t_sdl *sdl, t_array ret)
{
	t_component	current;

	current = init_button((t_button) {.pos = (t_pix) {WIDTH - 42, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events, .to_activate = (int *)&state->type,
		.img = parse_tga("./textures/ui/material_mode.tga", 0),
		.scancode = SDL_SCANCODE_UNKNOWN, .active_value = MATERIAL}, sdl);
	apush(&ret, &current);
	return (ret);
}

static t_array				init_childs(t_editor_root_state *state, t_env *env,
t_sdl *sdl)
{
	t_array		ret;
	t_component	current;

	ret = safe_anew(NULL, 5, sizeof(t_component), "components");
	current = init_editor_map(env, sdl);
	apush(&ret, &current);
	current = init_display_deco((t_display_deco_state) {.invert = 0,
		.to_look_at = (int *)&state->type, .display_value = (int)MATERIAL,
		.state = state}, init_editor_mat(env, sdl));
	apush(&ret, &current);
	current = init_simple_rectangle((t_pix) {WIDTH - 85, 1},
		(t_pix) {84, 42}, RICH_BLACK, sdl);
	apush(&ret, &current);
	current = init_button((t_button) {.pos = (t_pix) {WIDTH - 84, 2},
		.size = (t_pix) {40, 40}, .background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events, .to_activate = (int *)&state->type,
		.img = parse_tga("./textures/ui/map_mode.tga", 0),
		.scancode = SDL_SCANCODE_UNKNOWN, .active_value = MAP}, sdl);
	apush(&ret, &current);
	ret = init_childs_2(state, sdl, ret);
	return (ret);
}

static int					self_update(t_component *self, void *parent)
{
	t_env				*env;
	t_editor_root_state	*state;

	env = (t_env *)parent;
	state = (t_editor_root_state *)self->state;
	state->env = env;
	if (state && env->toggle_editor)
	{
		self->display = 1;
		return (1);
	}
	else
	{
		self->display = 0;
		return (0);
	}
}

static t_editor_root_state	*init_state(t_editor_root_state *state, t_env *env)
{
	state->type = MAP;
	state->env = env;
	return (state);
}

t_component					init_editor_root(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret.img.content = NULL;
	ret.text.text_texture = NULL;
	ret.size.x = WIDTH;
	ret.size.y = HEIGHT;
	ret.pos.x = 0;
	ret.pos.y = 0;
	ret.display = 1;
	ret.state = init_state((t_editor_root_state *)safe_malloc(
		sizeof(t_editor_root_state), "components"), env);
	ret.update = &self_update;
	ret.destroy = NULL;
	ret.render = NULL;
	ret.complete_render = &empty_render;
	ret.last_render = NULL;
	ret.childs = init_childs((t_editor_root_state *)ret.state, env, sdl);
	return (ret);
}
