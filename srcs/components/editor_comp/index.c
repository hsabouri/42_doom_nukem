/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:04:16 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/24 18:19:07 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../root.h"
#include "./editor_comp.h"
#include "./map/map.h"
#include "./materials/materials.h"
#include "../common/common.h"

static t_array				init_childs(t_editor_root_state *state, t_sdl *sdl)
{
	t_array		ret;
	t_component	current;

	ret = anew(NULL, 5, sizeof(t_component));
	current = init_editor_map(state->env, sdl);
	apush(&ret, &current);
	current = init_button((t_button) {
		.pos = (t_pix) {WIDTH - 42, HEIGHT - 42},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events,
		.img = parse_tga("./textures/ui/map_mode.tga"),
		.to_activate = (int *)&state->type,
		.active_value = MAP}, sdl);
	apush(&ret, &current);
	current =  init_button((t_button) {
		.pos = (t_pix) {WIDTH - 42, HEIGHT - 84},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events,
		.img = parse_tga("./textures/ui/event_mode.tga"),
		.to_activate = (int *)&state->type,
		.active_value = ACTION_EVENT}, sdl);
	apush(&ret, &current);
	current =  init_button((t_button) {
		.pos = (t_pix) {WIDTH - 42, HEIGHT - 126},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events,
		.img = parse_tga("./textures/ui/materials_mode.tga"),
		.to_activate = (int *)&state->type,
		.active_value = MATERIAL}, sdl);
	apush(&ret, &current);
	current =  init_button((t_button) {
		.pos = (t_pix) {WIDTH - 42, HEIGHT - 168},
		.size = (t_pix) {40, 40},
		.background = (t_color) {70, 70, 70, 255},
		.events = &state->env->events,
		.img = parse_tga("./textures/ui/entity_mode.tga"),
		.to_activate = (int *)&state->type,
		.active_value = ENTITY}, sdl);
	apush(&ret, &current);
/*
	current = init_editor_map();
	apush(&ret, &current);
	current = init_editor_map();
	apush(&ret, &current);
	current = init_editor_map();
	apush(&ret, &current);
	*/
	return (ret);
}

static int					self_update(t_component *self, void *parent)
{
	t_env	*env;

	env = (t_env *)parent;
	if (self->state && env->toggle_editor)
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
	ret.state = init_state((t_editor_root_state *)malloc(
		sizeof(t_editor_root_state)), env);
	ret.update = &self_update;
	ret.destroy = NULL;
	ret.render = NULL;
	ret.complete_render = &empty_render;
	ret.last_render = NULL;
	ret.childs = init_childs((t_editor_root_state *)ret.state, sdl);
	return (ret);
}
