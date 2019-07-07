/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:37:11 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/07 17:20:26 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"

static t_text	get_text(ssize_t id, t_sdl *sdl, size_t nentities)
{
	t_text	ret;
	char	*number;

	if ((size_t)id == nentities)
		ret = component_text("player", (t_pix) {0, 0}, sdl);
	else
	{
		number = ft_itoa((int)id);
		ret = component_text(number, (t_pix) {0, 0}, sdl);
		free(number);
	}
	return (ret);
}

static int		self_update(t_component *self, void *parent)
{
	const t_editor_map_state	*state = (t_editor_map_state *)self->state;
	static ssize_t				last = -1;
	ssize_t						new;

	(void)parent;
	new = (state->selected_entity >= 0)
		? state->selected_entity : state->selected_spawn;
	if (new != last)
	{
		last = new;
		SDL_DestroyTexture(self->text.text_texture);
		if (last >= 0)
			self->text = get_text(last, &state->env->sdl,
				state->env->game.nentities);
		else
			self->text = component_text("n/a", (t_pix) {0, 0},
				&state->env->sdl);
		return (1);
	}
	else
		return (0);
}

t_component		init_entity_info(t_editor_map_state *state, t_sdl *sdl)
{
	t_component	ret;

	ret = default_component(state, (t_pix) {0, 0}, sdl);
	ret.text = component_text("n/a", (t_pix) {0, 0}, sdl);
	ret.pos = (t_pix) {20, HEIGHT - 40};
	ret.complete_render = &empty_render;
	ret.update = &self_update;
	ret.childs = anew(NULL, 0, 0);
	ret.destroy = &no_destroy;
	return (ret);
}
