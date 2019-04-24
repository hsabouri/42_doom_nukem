/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_empty_life.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 11:21:10 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/15 11:21:11 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

static int				update_empty(t_component *self, void *parent)
{
	t_life_state	*life;
	char			*str;
	char			*tmp;

	life = (t_life_state *)parent;
	if (life->last_life != life->player->life)
	{
		life->pos.x = life->player->life * self->size.x / 100;
		str = ft_strdup(ft_itoa(life->player->life));
		tmp = str;
		str = ft_strjoin(str, "/100");
		ft_strdel(&tmp);
		self->text = component_text(str, (t_pix) {120, -2}, life->sdl);
		ft_strdel(&str);
		life->last_life = life->player->life;
		return (1);
	}
	return (0);
}

static void				render_empty(const t_component self, t_color *buf)
{
	t_life_state	*life;

	life = (t_life_state *)self.state;
	component_image(self.img, life->pos, self.size, buf);
}

t_array					init_empty_life(t_array array, void *parent_state,\
t_sdl *sdl)
{
	t_component		component;
	t_life_state	*life;
	char			*str;
	char			*tmp;

	life = (t_life_state *)parent_state;
	component.img = life->env->game.textures[15];
	component.size.x = component.img.width;
	component.size.y = component.img.height;
	str = ft_strdup(ft_itoa(life->player->life));
	tmp = str;
	str = ft_strjoin(str, "/100");
	ft_strdel(&tmp);
	component.text = component_text(str, (t_pix) {120, -2}, sdl);
	ft_strdel(&str);
	component.pos.x = 10;
	component.pos.y = 600;
	component.display = 1;
	component.state = parent_state;
	component.update = &update_empty;
	component.destroy = &no_destroy;
	component.render = &render_empty;
	component.childs = safe_anew(NULL, 1, sizeof(t_component), "component");
	component.complete_render = NULL;
	component.last_render = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, component.size.x,
		component.size.y);
	SDL_SetTextureBlendMode(component.last_render, SDL_BLENDMODE_BLEND);
	apush(&array, &component);
	return (array);
}

static void				render_full(const t_component self, t_color *buf)
{
	component_image(self.img, (t_pix) {0, 0}, self.size, buf);
}

t_array					init_full_life(t_array array, void *parent_state, \
t_sdl *sdl)
{
	t_component		component;
	t_life_state	*life;

	life = (t_life_state *)parent_state;
	component.img = life->env->game.textures[14];
	component.size.x = component.img.width;
	component.size.y = component.img.height;
	component.text.text_texture = NULL;
	component.pos.x = 10;
	component.pos.y = 600;
	component.display = 1;
	component.state = NULL;
	component.update = NULL;
	component.destroy = &no_destroy;
	component.render = &render_full;
	component.childs = safe_anew(NULL, 1, sizeof(t_component), "component");
	component.complete_render = NULL;
	component.last_render = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, component.size.x,
		component.size.y);
	SDL_SetTextureBlendMode(component.last_render, SDL_BLENDMODE_BLEND);
	apush(&array, &component);
	return (array);
}
