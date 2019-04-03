/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_lvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 12:51:03 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/30 12:51:04 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./menu.h"

int			new_map(void *parent_state)
{
	t_menu_state 			*menu;
	t_display_deco_state	*deco;

	deco = (t_display_deco_state *)parent_state;
	menu = (t_menu_state *)deco->state;
	menu->env->game_mode = 2;
	return (1);
}

int			new_game(void *parent_state)
{
	t_menu_state 			*menu;
	t_display_deco_state	*deco;

	deco = (t_display_deco_state *)parent_state;
	menu = (t_menu_state *)deco->state;
	menu->env->game_mode = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (1);
}

int			level_1(void *parent_state)
{
	t_menu_state 			*menu;

	menu = (t_menu_state *)parent_state;
	menu->env->game_mode = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (1);
}

int			level_2(void *parent_state)
{
	t_menu_state 			*menu;

	menu = (t_menu_state *)parent_state;
	menu->env->game_mode = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (1);
}

int			level_3(void *parent_state)
{
	t_menu_state 			*menu;

	menu = (t_menu_state *)parent_state;
	menu->env->game_mode = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (1);
}