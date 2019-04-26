/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:28:41 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/26 14:06:34 by lbougero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

static int				self_update(t_component *self, void *parent_state)
{
	t_hud_state		*hud;
	t_weapons_state	*self_state;
	t_img			**sprite;

	hud = (t_hud_state *)parent_state;
	self_state = (t_weapons_state *)self->state;
	if (self_state->last_equiped != hud->env->game.player.weapons
		[hud->env->game.player.equiped])
	{
		sprite = anth(&self_state->weapons[hud->env->game.player.weapons
			[hud->env->game.player.equiped]].sprite, 1);
		self->img = **sprite;
		self->pos.x = WIDTH / 2 - self->img.width / 2 + hud->env->game.weapons
			[hud->env->game.player.weapons
			[hud->env->game.player.equiped]].decal;
		self->pos.y = HEIGHT - self->img.height;
		self_state->last_equiped = hud->env->game.player.weapons
			[hud->env->game.player.equiped];
	}
	if (self_state->last_secondary != hud->env->game.player.secondary)
		self_state->last_secondary = hud->env->game.player.secondary;
	return (1);
}

static void				self_render(const t_component self, t_color *buf)
{
	background(buf, NO_COLOR, self.size);
	component_image(self.img, (t_pix) {0, 0}, self.size, buf);
}

static t_weapons_state	*init_weapon_state(void *parent_state)
{
	t_hud_state		*hud;
	t_weapons_state *state;

	hud = (t_hud_state *)parent_state;
	state = (t_weapons_state *)safe_malloc(sizeof(t_weapons_state),
		"components");
	state->sdl = &hud->env->sdl;
	state->weapons = hud->env->game.weapons;
	state->player = &hud->env->game.player;
	state->last_equiped = hud->env->game.player.weapons
		[hud->env->game.player.weapons[hud->env->game.player.equiped]];
	state->last_secondary = hud->env->game.player.secondary;
	return (state);
}

t_array					init_weapon(t_array array, void *parent_state,\
t_sdl *sdl)
{
	t_component	res;
	t_hud_state *hud;
	t_img		**sprite;

	hud = (t_hud_state *)parent_state;
	res.state = init_weapon_state(hud);
	sprite = anth(&hud->env->game.weapons[hud->env->game.player.weapons
		[hud->env->game.player.equiped]].sprite, 1);
	res.img = **sprite;
	res.text.text_texture = NULL;
	res.size.x = 500;
	res.size.y = 500;
	res.pos.x = WIDTH / 2 - res.img.width / 2 + 300;
	res.pos.y = HEIGHT - res.img.height;
	res.display = 1;
	res.update = &self_update;
	res.destroy = &no_destroy;
	res.render = &self_render;
	res.childs = safe_anew(NULL, 1, sizeof(t_component), "components");
	res.childs = mini_weapon(res.childs, res.state, sdl);
	res.childs = mini_weapon_s(res.childs, res.state, sdl);
	res.complete_render = NULL;
	res.last_render = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, res.size.x, res.size.y);
	SDL_SetTextureBlendMode(res.last_render, SDL_BLENDMODE_BLEND);
	apush(&array, &res);
	return (array);
}
