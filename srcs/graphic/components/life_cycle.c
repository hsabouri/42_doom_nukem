/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:47:42 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/30 17:08:14 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

#include "srcs/components/root.h"

SDL_Texture			*render_component(const t_component self, t_sdl *sdl)
{
	SDL_Texture	*texture;
	t_color		*content;
	int			trash;

	if (self.last_render == NULL)
		texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,\
			SDL_TEXTUREACCESS_STREAMING, self.size.x, self.size.y);
	else
		texture = ((t_component)self).last_render;
	SDL_LockTexture(texture, NULL, (void **)&content, (int *)&trash);
	if (self.render)
		self.render(self, content);
	SDL_UnlockTexture(texture);
	return (texture);
}

t_component			trigger_component(void *parent, t_component component,
t_sdl *sdl)
{
	t_component *child;
	size_t		i;

	if (!component.update || component.update(&component, parent))
	{
		i = 0;
		if (component.complete_render)
			component.last_render = component.complete_render(component, sdl);
		else
			component.last_render = render_component(component, sdl);
		while ((child = (t_component *)anth(&component.childs, i)) != NULL)
		{
			*child = trigger_component(component.state, *child, sdl);
			i++;
		}
	}
	return (component);
}

void				display_component(const t_component component, t_sdl *sdl)
{
	size_t		i;
	t_component	*child;

	i = 0;
	if (!component.display)
		return ;
	if (component.last_render)
		SDL_RenderCopy(sdl->renderer, component.last_render, NULL,
			&((SDL_Rect) {component.pos.x, component.pos.y, component.size.x,
				component.size.y}));
	if (component.text.text_texture)
		SDL_RenderCopy(sdl->renderer, component.text.text_texture, NULL,
			&((SDL_Rect){component.text.x + component.pos.x,
				component.text.y + component.pos.y, component.text.w,
				component.text.h}));
	while ((child = (t_component *)anth(&component.childs, i)) != NULL)
	{
		display_component(*child, sdl);
		i++;
	}
}

t_component			render_all(t_component component, t_sdl *sdl)
{
	t_component	*child;
	size_t		i;

	i = 0;
	if (component.complete_render)
		component.last_render = component.complete_render(component, sdl);
	else
		component.last_render = render_component(component, sdl);
	while ((child = (t_component *)anth(&component.childs, i)) != NULL)
	{
		*child = render_all(*child, sdl);
		i++;
	}
	return (component);
}

t_component			*init_component(t_env *env, t_sdl *sdl)
{
	t_component	*component;

	component = (t_component*)safe_malloc(sizeof(t_component), "components");
	*component = init_root(env, sdl);
	*component = render_all(*component, sdl);
	return (component);
}
