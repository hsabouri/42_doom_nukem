/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:01:47 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/08 15:01:54 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

static int					self_update(t_component *self, void *parent)
{
	t_hud_state			*hud;
	t_inventory_state	*state;

	hud = (t_hud_state *)parent;
	state = (t_inventory_state *)self->state;
	if (hud->env->events.keys[SDL_SCANCODE_I])
	{
		state->is_active = 1;
		self->display = 1;
		return (1);
	}
	else if (state->is_active && !hud->env->events.keys[SDL_SCANCODE_I])
	{
		state->is_active = 0;
		state->is_display = 0;
		self->display = 0;
		return (1);
	}
	return (0);
}

static void					render_inventoty(t_inventory_state *state,\
t_component self, t_color *buf)
{
	t_entity	**entity;
	t_mat		*mat;
	u_int32_t	decal_x;
	u_int32_t	decal_y;

	decal_x = 0;
	decal_y = 0;
	while ((entity = (t_entity **)apop(state->inventory_state)))
	{
		mat = *(t_mat **)anth(&(*entity)->mat, 0);
		if ((decal_x + mat->texture->width) >= WIDTH)
		{
			decal_y += 70;
			decal_x = 0;
		}
		component_image(*mat->texture, (t_pix) {20 + decal_x, 100 + decal_y},
				self.size, buf);
		decal_x += 50;
	}
}

static void					self_render(t_component self, t_color *buf)
{
	t_inventory_state	*state;
	t_color				bg;

	state = (t_inventory_state *)self.state;
	bg = state->background;
	if (state->is_active && !state->is_display)
	{
		bg.a = bg.a + 150;
		background(buf, bg, self.size);
		render_inventoty(state, self, buf);
		state->is_display = 1;
	}
}

static t_inventory_state	*init_inventory_state(void *parent_state)
{
	t_hud_state			*parent;
	t_inventory_state	*state;

	parent = (t_hud_state *)parent_state;
	state = (t_inventory_state *)safe_malloc(sizeof(t_inventory_state),
		"component");
	state->inventory_state = &parent->env->game.player.inventory;
	state->is_active = 0;
	state->is_display = 0;
	state->background = (t_color) {70, 70, 70, 0};
	return (state);
}

t_array						init_inventory(t_array array,\
void *parent_state, t_sdl *sdl)
{
	t_component	component;
	t_hud_state *hud;

	hud = (t_hud_state *)parent_state;
	component.img.content = NULL;
	component.size.x = WIDTH;
	component.size.y = HEIGHT;
	component.text = component_text("Inventory", (t_pix) {WIDTH / 2, 50}, sdl);
	component.pos.x = 0;
	component.pos.y = 0;
	component.display = 0;
	component.state = init_inventory_state(parent_state);
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