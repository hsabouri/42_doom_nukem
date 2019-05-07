/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/07 15:44:52 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./materials.h"
#include "../../common/common.h"

static void					self_render(const t_component self, t_color *buf)
{
	const t_editor_mat_state	state = *(t_editor_mat_state *)self.state;

	background(buf, RICH_BLACK, self.size);
}

static int					self_update(t_component *self, void *parent)
{
	t_editor_mat_state		*state;

	state = (t_editor_mat_state *)self->state;
	(void)parent;
	if (state->env->events.any)
		return (1);
	return (0);
}

static t_editor_mat_state	*init_state(t_editor_mat_state *state, t_env *env)
{
	state->env = env;
	state->selected = 0;
	state->selected_color = &env->game.materials[state->selected].color;
	state->selected_filter = &env->game.materials[state->selected].filter;
	return (state);
}

static t_array				init_childs(t_env *env, t_editor_mat_state *state,
t_sdl *sdl)
{
	t_array		ret;
	t_component	current;

	ret = safe_anew(NULL, 1, sizeof(t_component), "commponents");
	current = create_list_materials(env, sdl);
	apush(&ret, &current);
	current = init_preview(state, sdl);
	apush(&ret, &current);
	current = init_color_chooser(state, &state->selected_color,
		(t_pix) {505, 1}, sdl);
	apush(&ret, &current);
	current = init_color_chooser(state, &state->selected_filter,
		(t_pix) {808, 1}, sdl);
	apush(&ret, &current);
	return (ret);
}

t_component					init_editor_mat(t_env *env, t_sdl *sdl)
{
	t_component			ret;
	t_editor_mat_state	*state;

	state = (t_editor_mat_state *)safe_malloc(sizeof(t_editor_mat_state), "components");
	ret = default_component(state, (t_pix) {WIDTH, HEIGHT}, sdl);
	ret.state = init_state(ret.state, env);
	ret.pos.x = 0;
	ret.pos.y = 0;
	ret.display = 1;
	ret.update = &self_update;
	ret.destroy = NULL;
	ret.render = &self_render;
	ret.complete_render = NULL;
	ret.childs = init_childs(env, ret.state, sdl);
	return (ret);
}
