/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_lvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 12:51:03 by iporsenn          #+#    #+#             */
/*   Updated: 2019/04/16 10:51:06 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./menu.h"

int			new_map(void *parent_state)
{
	t_menu_state			*menu;
	t_display_deco_state	*deco;

	deco = (t_display_deco_state *)parent_state;
	menu = (t_menu_state *)deco->state;
	menu->env->game_mode = GAME_MODE;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (1);
}

int			new_game(void *parent_state)
{
	t_menu_state			*menu;
	t_display_deco_state	*deco;

	deco = (t_display_deco_state *)parent_state;
	menu = (t_menu_state *)deco->state;
	menu->env->game_mode = GAME_MODE;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (1);
}
