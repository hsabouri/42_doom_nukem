/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:04:24 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/26 16:24:38 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./menu.h"

static int			self_update(t_component *self, void *parent)
{
	t_env			*env;
	t_menu_state	*state;

	env = (t_env *)parent;
	state = (t_menu_state *)self->state;
	state->env = env;
	if (env)
		return (1);
	else
		return (0);
}

static void			self_render(const t_component self, t_color *buf)
{
	component_image(self.img, (t_pix) {0, 0}, self.size, buf);
}

static t_menu_state	*init_state(t_env *env)
{
	t_menu_state *state;

	state = safe_malloc(sizeof(t_component), "components");
	state->type = START_MODE;
	state->env = env;
	return (state);
}

t_component			*init_menu(t_env *env, t_sdl *sdl)
{
	t_component *ret;

	ret = (t_component *)safe_malloc(sizeof(t_component), "component");
	ret->display = 1;
	ret->pos.x = 0;
	ret->pos.y = 0;
	ret->size.x = WIDTH;
	ret->size.y = HEIGHT;
	ret->text.text_texture = NULL;
	ret->img = parse_tga("./textures/menu/menu_background.tga");
	ret->state = init_state(env);
	ret->render = &self_render;
	ret->complete_render = NULL;
	ret->update = &self_update;
	ret->destroy = NULL;
	ret->childs = safe_anew(NULL, 1, sizeof(t_component), "component");
	ret->childs = init_start_menu(ret->childs, sdl, ret->state);
	ret->childs = init_level_menu(ret->childs, sdl, ret->state);
	ret->last_render = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING, ret->size.x, ret->size.y);
	SDL_SetTextureBlendMode(ret->last_render, SDL_BLENDMODE_BLEND);
	return (ret);
}
