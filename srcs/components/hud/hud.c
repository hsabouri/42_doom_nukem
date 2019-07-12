/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:23:55 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 16:38:28 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"
#include "../common/common.h"
#include "./in_game_editor/in_game_editor.h"

static int			self_update(t_component *self, void *parent)
{
	t_env		*parent_state;
	t_hud_state	*state;

	parent_state = (t_env *)parent;
	state = (t_hud_state *)self->state;
	if (parent_state->toggle_editor == 0)
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

static t_hud_state	*init_state(t_env *env)
{
	t_hud_state *hud;

	hud = (t_hud_state *)safe_malloc(sizeof(t_hud_state), "components");
	hud->env = env;
	return (hud);
}

t_component			init_hud_root(t_env *env, t_sdl *sdl)
{
	t_component ret;
	t_component curr;

	ret = (t_component) {.img.content = NULL, .text.text_texture = NULL,
		.size.x = WIDTH, .size.y = HEIGHT, .pos.x = 0, .pos.y = 0,
		.display = 0, .state = init_state(env), .update = &self_update,
		.destroy = NULL, .render = NULL, .complete_render = &empty_render};
	ret.last_render = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, ret.size.x, ret.size.y);
	SDL_SetTextureBlendMode(ret.last_render, SDL_BLENDMODE_BLEND);
	ret.childs = safe_anew(NULL, 1, sizeof(t_component), "components");
	ret.childs = init_weapon(ret.childs, ret.state, sdl);
	ret.childs = init_life(ret.childs, ret.state, sdl);
	ret.childs = init_cross(ret.childs, ret.state, sdl);
	ret.childs = init_inventory(ret.childs, ret.state, sdl);
	ret.childs = init_help(ret.childs, ret.state, sdl);
	ret.childs = init_in_game_editor(ret.childs, env, sdl);
	curr = init_display_deco((t_display_deco_state){(int *)&env->game.nwalls,
			0, NULL, 0},
		init_simple_text("Cannot render: Press 'E' to enter the map editor",
			(t_pix) {WIDTH / 2 - 150, HEIGHT / 2 - 20}, sdl));
	apush(&ret.childs, &curr);
	return (ret);
}
