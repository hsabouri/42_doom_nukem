/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:59:18 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/15 14:59:19 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

t_array				init_mini_map(t_array array, void *parent_state, t_sdl *sdl)
{
	t_component	component;
	t_hud_state	*hud;

	hud = (t_hud_state *)parent_state;
	component.display = 1;
	component.img.content = NULL;
	component.size.x = WIDTH;
	component.size.y = HEIGHT;
	component.pos.x = 0;
	component.pos.y = 0;
	component.text = component_text("Mini map", (t_pix) {10, 10}, sdl);
	component.state = NULL;
	component.update = NULL;
	component.destroy = &no_destroy;
	component.render = NULL;
	component.childs = safe_anew(NULL, 1, sizeof(t_component), "component");
	component.complete_render = &empty_render;
	component.last_render = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, component.size.x,
		component.size.y);
	SDL_SetTextureBlendMode(component.last_render, SDL_BLENDMODE_BLEND);
	apush(&array, &component);
	return (array);
}
