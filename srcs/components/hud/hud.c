/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:23:55 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/23 17:18:03 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hud.h"

static t_array		init_childs(t_array array, t_env *env, t_sdl *sdl)
{
	// apush() child components here
	return (array);
}

static int			self_update(t_component *self, void *parent)
{
	t_env		*parent_state;
	t_hud_state	*state;

	parent_state = (t_env *)parent;
	state = (t_hud_state *)self->state;
	if (parent_state->toggle_editor == 0)
	{
		self->display = 1;
		return (1);
	}
	else
	{
		self->display = 0;
		return (0);
	}
}

static t_hud_state	*init_state(t_hud_state *state, t_env *env)
{
	// State initialisation goes here
	return (state);
}

t_component			init_hud_root(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret.img.content = NULL;
	ret.text = component_text("HUD displayed", (t_pix) {10, 100}, sdl);
	ret.size.x = WIDTH;
	ret.size.y = HEIGHT;
	ret.pos.x = 0;
	ret.pos.y = 0;
	ret.display = 1;
	ret.state = init_state((t_hud_state *)safe_malloc(
		sizeof(t_hud_state), "components"), env);
	ret.update = &self_update;
	ret.destroy = NULL; // Will automatically destroy component
	ret.complete_render = &empty_render; // Will not draw anythin for this component
	ret.last_render = NULL;
	ret.childs = safe_anew(NULL, 0, sizeof(t_component), "components");
	ret.childs = init_childs(ret.childs, env, sdl);
	return (ret);
}