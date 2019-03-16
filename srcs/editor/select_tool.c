/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:18:47 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/16 11:28:48 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_tool	editor_select_tool(t_env env)
{
	t_tool	res;

	if (env.events.keys[SDL_SCANCODE_O] == 1)
		res = WALL;
	else if (env.events.keys[SDL_SCANCODE_P] == 1)
		res = POINT;
	else if (env.events.keys[SDL_SCANCODE_I] == 1)
		res = PORTAL;
	else
		res = env.editor.current_tool;
	env.events.keys[SDL_SCANCODE_P] = 0;
	env.events.keys[SDL_SCANCODE_O] = 0;
	env.events.keys[SDL_SCANCODE_I] = 0;
	env.events.keys[SDL_SCANCODE_U] = 0;
	return (res);
}