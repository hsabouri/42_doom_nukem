/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_button.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:00:44 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/28 15:00:45 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./menu.h"

t_array		init_start_button_3(t_array childs, t_sdl *sdl, t_menu_state *state)
{
	t_component	current;

	current = init_button((t_button) {.pos = (t_pix) {96, 664},
		.size = (t_pix) {256, 56}, .background = NO_COLOR,
		.events = &state->env->events, .active_value = START_MODE,
		.img = parse_tga("./textures/menu/return.tga", 0),
		.img_active = parse_tga("./textures/menu/return_active.tga", 0),
		.to_activate = (int *)&state->type,
		.scancode = SDL_SCANCODE_UNKNOWN}, sdl);
	apush(&childs, &current);
	return (childs);
}
