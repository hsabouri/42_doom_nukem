/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 12:07:00 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 16:27:52 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./root.h"
#include "./hud/hud.h"
#include "./editor_comp/editor_comp.h"

static t_array	init_childs(t_array array, t_env *env, t_sdl *sdl)
{
	t_component current;

	current = init_editor_root(env, sdl);
	apush(&array, &current);
	current = init_hud_root(env, sdl);
	apush(&array, &current);
	current = init_dead(env, sdl);
	apush(&array, &current);
	current = init_win(env, sdl);
	apush(&array, &current);
	return (array);
}

static int		self_update(t_component *self, void *parent)
{
	t_env	*env;

	env = (t_env *)parent;
	self->state = env;
	if (env)
		return (1);
	else
		return (0);
}

t_component		init_root(t_env *env, t_sdl *sdl)
{
	t_component ret;

	ret.img.content = NULL;
	ret.text.text_texture = NULL;
	ret.size.x = WIDTH;
	ret.size.y = HEIGHT;
	ret.pos.x = 0;
	ret.pos.y = 0;
	ret.display = 1;
	ret.state = env;
	ret.update = &self_update;
	ret.destroy = &no_destroy;
	ret.render = NULL;
	ret.complete_render = &empty_render;
	ret.last_render = NULL;
	ret.childs = safe_anew(NULL, 2, sizeof(t_component), "component");
	ret.childs = init_childs(ret.childs, env, sdl);
	return (ret);
}
