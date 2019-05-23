/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:23:55 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/23 12:15:13 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"
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

	ret.img.content = NULL;
	ret.text.text_texture = NULL;
	ret.size.x = WIDTH;
	ret.size.y = HEIGHT;
	ret.pos.x = 0;
	ret.pos.y = 0;
	ret.display = 0;
	ret.state = init_state(env);
	ret.update = &self_update;
	ret.destroy = NULL;
	ret.render = NULL;
	ret.complete_render = &empty_render;
	ret.last_render = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, ret.size.x, ret.size.y);
	SDL_SetTextureBlendMode(ret.last_render, SDL_BLENDMODE_BLEND);
	ret.childs = safe_anew(NULL, 1, sizeof(t_component), "components");
	ret.childs = init_weapon(ret.childs, ret.state, sdl);
	ret.childs = init_life(ret.childs, ret.state, sdl);
	ret.childs = init_cross(ret.childs, ret.state, sdl);
	ret.childs = init_mini_map(ret.childs, ret.state, sdl);
	ret.childs = init_inventory(ret.childs, ret.state, sdl);
	ret.childs = init_help(ret.childs, ret.state, sdl);
	ret.childs = init_in_game_editor(ret.childs, env, sdl);
	return (ret);
}
