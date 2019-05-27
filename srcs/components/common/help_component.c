/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_component.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:44:18 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/27 11:36:39 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./common.h"

static void	self_render(const t_component self, t_color *buf)
{
	t_help_state	*state;
	t_color			bg;

	state = (t_help_state *)self.state;
	bg = (t_color) {70, 70, 70, 0};
	bg.a = bg.a + 150;
	background(buf, bg, self.size);
	component_image(self.img, (t_pix) {(WIDTH / 2 - self.img.width / 2),
		(HEIGHT / 2 - self.img.height / 2)}, self.size, buf);
}

t_component	init_help_component(t_help_state state, t_sdl *sdl)
{
	t_component ret;

	ret.img.content = NULL;
	if (state.img.content != NULL)
		ret.img = state.img;
	ret.text.text_texture = NULL;
	ret.size.x = WIDTH;
	ret.size.y = HEIGHT;
	ret.pos = (t_pix) {0, 0};
	ret.display = 1;
	ret.state = NULL;
	ret.update = NULL;
	ret.render = &self_render;
	ret.complete_render = NULL;
	ret.destroy = NULL;
	ret.last_render = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, ret.size.x,
		ret.size.y);
	SDL_SetTextureBlendMode(ret.last_render, SDL_BLENDMODE_BLEND);
	ret.childs = safe_anew(NULL, 1, sizeof(t_component), "components");
	return (ret);
}
