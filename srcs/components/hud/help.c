/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:21:20 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/03 10:19:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

static int					self_update(t_component *self, void *parent)
{
	t_hud_state			*hud;
	t_help_comp_state	*state;

	hud = (t_hud_state *)parent;
	state = (t_help_comp_state *)self->state;
	if (hud->env->events.keys[SDL_SCANCODE_H])
	{
		state->is_active = 1;
		self->display = 1;
		if (hud->env->editor.enabled == 1 && hud->env->toggle_editor == 0)
			state->img_display = 1;
		else
			state->img_display = 0;
		return (1);
	}
	else if (state->is_active && !hud->env->events.keys[SDL_SCANCODE_H])
	{
		state->is_active = 0;
		state->is_display = 0;
		self->display = 0;
		return (1);
	}
	return (0);
}

static void					self_render(const t_component self, t_color *buf)
{
	t_help_comp_state	*state;
	t_color				bg;

	state = (t_help_comp_state *)self.state;
	bg = state->background;
	if (state->is_active && !state->is_display)
	{
		bg.a = bg.a + 150;
		background(buf, bg, self.size);
		if (state->img_display == 0)
			component_image(state->help, (t_pix) {(WIDTH / 2 - state->help.width
				/ 2), (HEIGHT / 2 - state->help.height / 2)}, self.size, buf);
		else
			component_image(state->help_ig_edit, (t_pix) {(WIDTH / 2
				- state->help.width / 2), (HEIGHT / 2 - state->help.height
				/ 1.3)}, self.size, buf);
		state->is_display = 1;
	}
}

static t_help_comp_state	*init_help_comp_state(void *parent_state)
{
	t_hud_state			*hud;
	t_help_comp_state	*state;

	hud = (t_hud_state *)parent_state;
	state = (t_help_comp_state *)safe_malloc(sizeof(t_help_comp_state),
		"component");
	state->help = hud->env->game.textures[16];
	state->help_ig_edit = hud->env->game.textures[36];
	state->is_active = 0;
	state->is_display = 0;
	state->img_display = 0;
	state->background = (t_color) {70, 70, 70, 0};
	return (state);
}

t_array						init_help(t_array array, void *parent_state,
t_sdl *sdl)
{
	t_component	component;
	t_hud_state *hud;

	hud = (t_hud_state *)parent_state;
	component.img.content = NULL;
	component.size.x = WIDTH;
	component.size.y = HEIGHT;
	component.text = component_text("Help", (t_pix) {WIDTH / 2, 50}, sdl);
	component.pos.x = 0;
	component.pos.y = 0;
	component.display = 0;
	component.state = init_help_comp_state(parent_state);
	component.update = &self_update;
	component.destroy = &no_destroy;
	component.render = &self_render;
	component.childs = safe_anew(NULL, 1, sizeof(t_component), "component");
	component.complete_render = NULL;
	component.last_render = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, component.size.x,
		component.size.y);
	SDL_SetTextureBlendMode(component.last_render, SDL_BLENDMODE_BLEND);
	apush(&array, &component);
	return (array);
}
