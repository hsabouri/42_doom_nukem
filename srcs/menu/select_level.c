/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_level.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:24:43 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/07 19:56:24 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./menu.h"

static t_array	init_start_button_2(t_array childs, t_sdl *sdl,
t_menu_state *state)
{
	t_component	current;

	current = init_cb_button((t_cb_button) {.pos = (t_pix) {96, 416},
		.size = (t_pix) {256, 56}, .background = NO_COLOR,
		.events = &state->env->events, .callback = &level_1,
		.img = parse_tga("./textures/menu/level_1.tga", 0),
		.img_active = parse_tga("./textures/menu/level_1_active.tga", 0),
		.scancode = SDL_SCANCODE_UNKNOWN}, sdl);
	apush(&childs, &current);
	current = init_cb_button((t_cb_button) {.pos = (t_pix) {96, 467},
		.size = (t_pix) {256, 56}, .background = NO_COLOR,
		.events = &state->env->events, .callback = &level_2,
		.img = parse_tga("./textures/menu/level_2.tga", 0),
		.img_active = parse_tga("./textures/menu/level_2_active.tga", 0),
		.scancode = SDL_SCANCODE_UNKNOWN}, sdl);
	apush(&childs, &current);
	current = init_cb_button((t_cb_button) {.pos = (t_pix) {96, 518},
		.size = (t_pix) {256, 56}, .background = NO_COLOR,
		.events = &state->env->events, .callback = &level_3,
		.img = parse_tga("./textures/menu/level_3.tga", 0),
		.img_active = parse_tga("./textures/menu/level_3_active.tga", 0),
		.scancode = SDL_SCANCODE_UNKNOWN}, sdl);
	apush(&childs, &current);
	return (childs);
}

static t_array	init_start_button(t_array childs, t_sdl *sdl,
t_menu_state *state)
{
	t_component	current;

	current = init_display_deco((t_display_deco_state) {.invert = 0,
		.to_look_at = (int *)&state->type, .display_value = NEW_GAME,
		.state = state}, init_cb_button((t_cb_button) {.pos = (t_pix) {96, 365},
		.size = (t_pix) {256, 56}, .background = NO_COLOR,
		.events = &state->env->events, .callback = &new_game,
		.img = parse_tga("./textures/menu/new_game.tga", 0),
		.img_active = parse_tga("./textures/menu/new_game_active.tga", 0),
		.scancode = SDL_SCANCODE_UNKNOWN}, sdl));
	apush(&childs, &current);
	current = init_display_deco((t_display_deco_state) {.invert = 0,
		.to_look_at = (int *)&state->type, .display_value = NEW_MAP,
		.state = state}, init_cb_button((t_cb_button) {.pos = (t_pix) {96, 365},
		.size = (t_pix) {256, 56}, .background = NO_COLOR,
		.events = &state->env->events, .callback = &new_map,
		.img = parse_tga("./textures/menu/new_level.tga", 0),
		.img_active = parse_tga("./textures/menu/new_level_active.tga", 0),
		.scancode = SDL_SCANCODE_UNKNOWN}, sdl));
	apush(&childs, &current);
	if (state->env->file && ft_strcmp(state->env->file, "nyan_dukem") == 0)
		childs = init_start_button_2(childs, sdl, state);
	childs = init_start_button_3(childs, sdl, state);
	return (childs);
}

static int		self_update(t_component *self, void *parent)
{
	const t_menu_state	*parent_state = (t_menu_state *)parent;

	if (self->display == 0
		&& (parent_state->type == NEW_GAME || parent_state->type == NEW_MAP))
	{
		self->display = 1;
		return (1);
	}
	else if (self->display == 1
		&& !(parent_state->type == NEW_GAME || parent_state->type == NEW_MAP))
	{
		self->display = 0;
		return (1);
	}
	if (self->display == 1 && parent_state->env->events.any)
		return (1);
	return (0);
}

static void		self_render(const t_component self, t_color *buf)
{
	component_image(self.img, (t_pix) {0, 0}, self.size, buf);
}

t_array			init_level_menu(t_array childs, t_sdl *sdl,
t_menu_state *state)
{
	t_component	current;

	current.display = 1;
	current.pos.x = 0;
	current.pos.y = 0;
	current.size.x = WIDTH;
	current.size.y = HEIGHT;
	current.text.text_texture = NULL;
	current.img.content = NULL;
	current.state = state;
	current.render = &self_render;
	current.complete_render = NULL;
	current.update = &self_update;
	current.destroy = &no_destroy;
	current.childs = safe_anew(NULL, 1, sizeof(t_component), "component");
	current.childs = init_start_button(current.childs, sdl, state);
	current.last_render = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, current.size.x,
		current.size.y);
	SDL_SetTextureBlendMode(current.last_render, SDL_BLENDMODE_BLEND);
	apush(&childs, &current);
	return (childs);
}
