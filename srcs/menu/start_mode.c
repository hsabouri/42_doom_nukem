/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:44:43 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/03 14:58:08 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

static int		quit(void *parent_state)
{
	t_menu_state *menu;

	menu = (t_menu_state *)parent_state;
	menu->env->game_mode = QUIT;
	return (1);
}

static t_array	init_start_button(t_array childs, t_sdl *sdl,\
t_menu_state *state)
{
	t_component	current;

	current = init_button((t_button) {.pos = (t_pix) {96, 365},
		.size = (t_pix) {256, 56}, .background = NO_COLOR,
		.events = &state->env->events, .active_value = NEW_GAME,
		.img = parse_tga("./textures/menu/start_game.tga", 0),
		.img_active = parse_tga("./textures/menu/start_game_active.tga", 0),
		.to_activate = (int *)&state->type,
		.scancode = SDL_SCANCODE_UNKNOWN}, sdl);
	apush(&childs, &current);
	current = init_button((t_button) {.pos = (t_pix) {96, 416},
		.size = (t_pix) {256, 56}, .background = NO_COLOR,
		.events = &state->env->events, .active_value = NEW_MAP,
		.img = parse_tga("./textures/menu/start_editor.tga", 0),
		.img_active = parse_tga("./textures/menu/start_editor_active.tga", 0),
		.to_activate = (int *)&state->type,
		.scancode = SDL_SCANCODE_UNKNOWN}, sdl);
	apush(&childs, &current);
	current = init_cb_button((t_cb_button) {.pos = (t_pix) {96, 664},
		.size = (t_pix) {256, 56}, .background = NO_COLOR, .callback = &quit,
		.events = &state->env->events, .scancode = SDL_SCANCODE_UNKNOWN,
		.img_active = parse_tga("./textures/menu/quit_game_active.tga", 0),
		.img = parse_tga("./textures/menu/quit_game.tga", 0)}, sdl);
	apush(&childs, &current);
	return (childs);
}

static int		self_update(t_component *self, void *parent)
{
	const t_menu_state	*parent_state = (t_menu_state *)parent;

	if (self->display == 1 && parent_state->type != START_MODE)
	{
		if (parent_state->type == NEW_MAP)
			parent_state->env->editor.enabled = 1;
		self->display = 0;
		return (1);
	}
	else if (self->display == 0 && parent_state->type == START_MODE)
	{
		self->display = 1;
		return (1);
	}
	else if (self->display == 1 && parent_state->env->events.any)
		return (1);
	return (0);
}

static void		self_render(const t_component self, t_color *buf)
{
	component_image(self.img, (t_pix) {0, 0}, self.size, buf);
}

t_array			init_start_menu(t_array childs, t_sdl *sdl,
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
		SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
		current.size.x, current.size.y);
	SDL_SetTextureBlendMode(current.last_render, SDL_BLENDMODE_BLEND);
	apush(&childs, &current);
	return (childs);
}
