/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_empty_life.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 11:21:10 by iporsenn          #+#    #+#             */
/*   Updated: 2019/07/06 12:54:36 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

static int				update_empty(t_component *self, void *parent)
{
	t_life_state	*life;
	char			*str;
	char			*tmp;

	life = (t_life_state *)parent;
	if (life->last_life != life->player->my_entity.life)
	{
		life->pos.x = life->player->my_entity.life * self->img.width / 100;
		str = ft_itoa(life->player->my_entity.life);
		tmp = str;
		str = ft_strjoin(str, "/100");
		ft_strdel(&tmp);
		self->text = component_text(str, (t_pix) {120, -2}, life->sdl);
		ft_strdel(&str);
		life->last_life = life->player->my_entity.life;
		return (1);
	}
	return (0);
}

static void				render_empty(const t_component self, t_color *buf)
{
	t_life_state	*life;

	life = (t_life_state *)self.state;
	background(buf, NO_COLOR, self.size);
	component_image(self.img, life->pos,
		(t_pix){self.img.width, self.img.height}, buf);
}

t_array					init_empty_life(t_array array, void *parent_state,
t_sdl *sdl)
{
	t_component		component;
	t_life_state	*life;
	char			*str;
	char			*tmp;

	life = (t_life_state *)parent_state;
	str = ft_itoa(life->player->my_entity.life);
	tmp = str;
	str = ft_strjoin(str, "/100");
	ft_strdel(&tmp);
	component = (t_component) {.img = life->env->game.textures[15],
		.pos.x = 10, .pos.y = 600, .display = 1, .state = parent_state,
		.update = &update_empty, .destroy = &no_destroy,
		.render = &render_empty, .complete_render = NULL,
		.childs = safe_anew(NULL, 1, sizeof(t_component), "component"),
		.text = component_text(str, (t_pix) {120, -2}, sdl)};
	component.size.x = component.img.width;
	component.size.y = component.img.height;
	component.last_render = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, component.size.x,
		component.size.y);
	SDL_SetTextureBlendMode(component.last_render, SDL_BLENDMODE_BLEND);
	apush(&array, &component);
	ft_strdel(&str);
	return (array);
}

static void				render_full(const t_component self, t_color *buf)
{
	component_image(self.img, (t_pix) {0, 0}, self.size, buf);
}

t_array					init_full_life(t_array array, void *parent_state,
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
