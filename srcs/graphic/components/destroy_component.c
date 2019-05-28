/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_component.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:53:43 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/27 10:54:05 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

#include "srcs/components/root.h"

void	destroy_component(t_component *component)
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
	if (component->childs.mem)
		free(component->childs.mem);
}
