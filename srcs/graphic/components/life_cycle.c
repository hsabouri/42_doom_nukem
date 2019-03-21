/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:47:42 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/21 16:19:19 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

#include "srcs/components/sample_button.h"

SDL_Texture		*render_component(const t_component self, t_sdl *sdl)
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

t_component		trigger_component(t_env env, t_component component, t_sdl *sdl)
{
	t_component *child;
	size_t		i;

    if (!component.update || component.update(&component, &env))
	{
		i = 0;
    	component.last_render = render_component(component, sdl);
		while ((child = (t_component *)anth(&component.childs, i)) != NULL)
		{
    		*child = trigger_component(env, *child, sdl);
			i++;
		}
	}
	return (component);
}

void			display_component(const t_component component, t_sdl *sdl)
{
	size_t		i;
	t_component	*child;

	i = 0;
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

void			destroy_component(t_component *component)
{
	t_component	*current;

	if (!component)
		return ;
	while ((current = (t_component *)apop(&component->childs)))
		destroy_component(current);
	if (!component->destroy)
		free(component->state);
	else
		component->destroy(component);
	if (component->text.text_texture)
		SDL_DestroyTexture(component->text.text_texture);
	if (component->img.content)
		free(component->img.content);
	if (component->last_render)
		SDL_DestroyTexture(component->last_render);
}


t_component		*init_component(t_sdl *sdl)
{
	t_component	*component;

	component = (t_component*)malloc(sizeof(t_component));
	*component = init_button("Sample", sdl);
	return (component);
}