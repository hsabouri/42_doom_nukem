/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:04:16 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/23 16:01:32 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../root.h"
#include "./editor.h"

static t_array				init_childs(t_env *env, t_sdl *sdl)
{
	t_array		ret;
	t_component	current;

	ret = anew(NULL, 5, sizeof(t_component));
	current = init_editor_map(env, sdl);
	apush(&ret, &current);
	/*
	current = init_editor_map();
	apush(&ret, &current);
	current = init_editor_map();
	apush(&ret, &current);
	current = init_editor_map();
	apush(&ret, &current);
	*/
	return (ret);
}

static int					self_update(t_component *self, void *parent)
{
	t_env	*env;

	env = (t_env *)parent;
	if (self->state && env->toggle_editor)
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

static t_editor_root_state	*init_state(t_editor_root_state *state, t_env *env)
{
	state->type = MAP;
	state->env = env;
	return (state);
}

t_component					init_editor_root(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret.img.content = NULL;
	ret.text = component_text("Editor3030", (t_pix) {10, 10}, sdl);
	ret.size.x = WIDTH;
	ret.size.y = HEIGHT;
	ret.pos.x = 0;
	ret.pos.y = 0;
	ret.display = 1;
	ret.state = init_state((t_editor_root_state *)malloc(
		sizeof(t_editor_root_state)), env);
	ret.update = &self_update;
	ret.destroy = NULL;
	ret.render = NULL;
	ret.complete_render = &empty_render;
	ret.last_render = NULL;
	ret.childs = init_childs(env, sdl);
	return (ret);
}
