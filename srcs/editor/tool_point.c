/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:48:59 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/16 11:31:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_env	point_tool(t_env env)
{
	env.editor.points_wall[0] = -1;
	env.editor.points_wall[1] = -1;
	env.editor.sel_point = select_point(env.game, env.editor, env.events);
	if (env.editor.sel_point >= 0 && env.events.mouse[SDL_BUTTON_LEFT])
		env.game.points[env.editor.sel_point] = point_from_mouse(env.events, env.editor);
	else if (env.editor.sel_point >= 0 && env.events.mouse_click[SDL_BUTTON_RIGHT])
		env.game = delete_point(env.editor.sel_point, env.game);
	else if (env.editor.sel_point == -1 && env.events.mouse_click[SDL_BUTTON_RIGHT])
		env.game = create_point(point_from_mouse(env.events, env.editor), -1, env.game);
	env.editor.selecting = env.events.mouse[SDL_BUTTON_LEFT];
	return (env);
}