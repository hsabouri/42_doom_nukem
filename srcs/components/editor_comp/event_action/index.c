/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/14 15:44:42 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ev_ac.h"
#include "../../common/common.h"

static void					self_render(const t_component self, t_color *buf)
{
	const t_editor_ev_ac_state	state = *(t_editor_ev_ac_state *)self.state;

	background(buf, RICH_BLACK, self.size);
	if (state.selected >= 0)
		component_image(self.img, (t_pix) {202, 2},
			(t_pix) {WIDTH, HEIGHT}, buf);
	if (state.selected_entity >= 0)
		component_image(self.img, (t_pix) {422, 2},
			(t_pix) {WIDTH, HEIGHT}, buf);
	if (state.selected_trigger >= 0)
		component_image(self.img, (t_pix) {644, 2},
			(t_pix) {WIDTH, HEIGHT}, buf);
}

static int					self_update(t_component *self, void *parent)
{
	t_editor_ev_ac_state		*state;

	state = (t_editor_ev_ac_state *)self->state;
	(void)parent;
	if (state->env->events.any)
		return (1);
	return (0);
}

static t_editor_ev_ac_state	*init_state(t_editor_ev_ac_state *state, t_env *env)
{
	state->env = env;
	state->selected = -1;
	state->selected_trigger = -1;
	state->selected_entity = -1;
	return (state);
}

static t_array				init_childs(t_env *env, t_editor_ev_ac_state *state,
t_sdl *sdl)
{
	t_array		ret;
	t_component	current;

	ret = safe_anew(NULL, 1, sizeof(t_component), "commponents");
	current = create_list_events(env, sdl);
	apush(&ret, &current);
	current = create_list_events(env, sdl);
	apush(&ret, &current);
	current = init_display_deco((t_display_deco_state) {
		(int *)&state->selected, -1, state, 1
	}, create_list_entity(env, sdl));
	apush(&ret, &current);
	current = init_display_deco((t_display_deco_state) {
		(int *)&state->selected_entity, -1, state, 1
	}, create_list_trigger(env, sdl));
	apush(&ret, &current);
	current = init_display_deco((t_display_deco_state) {
		(int *)&state->selected_trigger, -1, state, 1
	}, create_list_seconds_entity(env, &state->refresh_second_entity, sdl));
	apush(&ret, &current);
	return (ret);
}

t_component					init_editor_ev_ac(t_env *env, t_sdl *sdl)
{
	t_component			ret;
	t_editor_ev_ac_state	*state;

	state = (t_editor_ev_ac_state *)safe_malloc(sizeof(t_editor_ev_ac_state), "components");
	ret = default_component(state, (t_pix) {WIDTH, HEIGHT}, sdl);
	ret.state = init_state(ret.state, env);
	ret.img = parse_tga("./textures/ui/arrow-right.tga");
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