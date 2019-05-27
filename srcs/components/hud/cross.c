/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:15:44 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/14 17:15:47 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

static void			self_render(const t_component self, t_color *buf)
{
	component_image(self.img, (t_pix) {0, 0}, self.size, buf);
}

t_array				init_cross(t_array array, void *parent_state,
t_sdl *sdl)
{
	t_component	component;
	t_hud_state *hud;

	hud = (t_hud_state *)parent_state;
	component.img = hud->env->game.textures[13];
	component.size.x = component.img.width;
	component.size.y = component.img.height;
	component.text.text_texture = NULL;
	component.pos.x = WIDTH / 2 - component.img.width / 2;
	component.pos.y = HEIGHT / 2 - component.img.height / 2;
	component.display = 1;
	component.state = NULL;
	component.update = NULL;
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
