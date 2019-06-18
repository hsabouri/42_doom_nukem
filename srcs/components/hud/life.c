/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:36:06 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/18 15:32:39 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

static int				self_update(t_component *self, void *parent)
{
	t_hud_state		*hud;
	t_life_state	*life;

	hud = (t_hud_state *)parent;
	life = (t_life_state *)self->state;
	if (life->last_life != hud->env->game.player.my_entity.life)
		life->display = 1;
	return (1);
}

static void				self_render(const t_component self, t_color *buf)
{
	t_life_state *life;

	life = (t_life_state *)self.state;
	if (life->display == 1)
	{
		background(buf, (t_color) {255, 0, 0, 50}, self.size);
		life->display = 0;
	}
	else if (life->player->my_entity.life <= 20)
		background(buf, (t_color) {255, 0, 0, 20}, self.size);
	else
		background(buf, NO_COLOR, self.size);
}

static t_life_state		*init_life_state(void *parent_state)
{
	t_hud_state		*hud;
	t_life_state	*state;

	hud = (t_hud_state *)parent_state;
	state = (t_life_state *)safe_malloc(sizeof(t_life_state), "components");
	state->env = hud->env;
	state->player = &hud->env->game.player;
	state->last_life = hud->env->game.player.my_entity.life;
	state->empty_life = hud->env->game.textures[15];
	state->pos.x = state->player->my_entity.life
		* state->empty_life.width / 100;
	state->pos.y = 0;
	state->display = 0;
	state->sdl = &hud->env->sdl;
	return (state);
}

t_array					init_life(t_array array, void *parent_state, t_sdl *sdl)
{
	t_component	component;
	t_hud_state *hud;

	hud = (t_hud_state *)parent_state;
	component.img.content = NULL;
	component.size.x = WIDTH;
	component.size.y = HEIGHT;
	component.text.text_texture = NULL;
	component.pos.x = 0;
	component.pos.y = 0;
	component.display = 1;
	component.state = init_life_state(hud);
	component.update = &self_update;
	component.destroy = &no_destroy;
	component.render = &self_render;
	component.childs = safe_anew(NULL, 1, sizeof(t_component), "component");
	component.childs = init_full_life(component.childs, component.state, sdl);
	component.childs = init_empty_life(component.childs, component.state, sdl);
	component.complete_render = NULL;
	component.last_render = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, component.size.x,
		component.size.y);
	SDL_SetTextureBlendMode(component.last_render, SDL_BLENDMODE_BLEND);
	apush(&array, &component);
	return (array);
}
