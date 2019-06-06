/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:13:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/06 10:47:08 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./in_game_editor.h"
#include "../../common/common.h"

static t_component	init_childs(t_array *childs, t_sdl *sdl,
t_button button)
{
	t_component curr;

	curr = init_button(button, sdl);
	free(button.place_holder);
	apush(childs, &curr);
	button.place_holder = ft_strdup("[Y] MAT TEXTURE POSITION");
	button.pos = (t_pix) {curr.pos.x, curr.pos.y + curr.size.y + 2};
	button.active_value = MATERIAL_MOVE;
	curr = init_button(button, sdl);
	free(button.place_holder);
	apush(childs, &curr);
	button.place_holder = ft_strdup("[U] MAT TEXTURE SCALE");
	button.pos = (t_pix) {curr.pos.x, curr.pos.y + curr.size.y + 2};
	button.active_value = MATERIAL_SCALE;
	curr = init_button(button, sdl);
	free(button.place_holder);
	apush(childs, &curr);
	button.place_holder = ft_strdup("[G] MATERIAL CHANGE");
	button.pos = (t_pix) {curr.pos.x, curr.pos.y + curr.size.y + 2};
	button.active_value = MATERIAL_CHANGE;
	curr = init_button(button, sdl);
	free(button.place_holder);
	apush(childs, &curr);
	return (curr);
}

t_array				init_in_game_editor(t_array childs, t_env *env, t_sdl *sdl)
{
	t_component	comp;
	t_component	curr;
	t_button	button;

	comp = default_component(NULL, (t_pix) {0, 0}, sdl);
	comp.childs = anew(NULL, 5, sizeof(t_component));
	button = (t_button) { .pos = (t_pix) {2, 2}, .size = (t_pix) {0, 0},
		.background = (t_color) {70, 70, 70, 200}, .events = &env->events,
		.place_holder = ft_strdup("[T] WALL TEXTURE POSITION"),
		.to_activate = (int *)&env->editor.game_tool,
		.active_value = TEXTURE_MOVE};
	curr = init_childs(&comp.childs, sdl, button);
	button.place_holder = ft_strdup("[J] SECTOR HEIGHT");
	button.pos = (t_pix) {curr.pos.x, curr.pos.y + curr.size.y + 2};
	button.active_value = SECTOR_HEIGHT;
	curr = init_button(button, sdl);
	free(button.place_holder);
	apush(&comp.childs, &curr);
	curr = init_display_deco((t_display_deco_state) {&env->editor.enabled, 1,
		NULL, 0}, comp);
	apush(&childs, &curr);
	return (childs);
}
