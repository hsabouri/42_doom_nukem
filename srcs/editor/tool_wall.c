/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:50:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/09 14:57:56 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_env	wall_tool(t_env env)
{
	env.editor.sel_point = select_point(env.game, env.editor, env.events);
	env.editor.sel_wall = select_wall(env.game, env.editor, env.events);
	env.editor = select_multi_points(env.editor, env.events, env.editor.sel_point);
	if ((size_t)env.editor.points_wall[0] >= env.game.npoints)
		env.editor.points_wall[0] = -1;
	if ((size_t)env.editor.points_wall[1] >= env.game.npoints)
		env.editor.points_wall[1] = -1;
	if (env.editor.points_wall[0] >= 0 && env.editor.points_wall[1] >= 0)
	{
		env.game = create_wall(env.editor.points_wall, 0, env.game);
		env.editor.points_wall[0] = -1;
	}
	if (env.editor.sel_wall >= 0 && env.events.mouse_click[SDL_BUTTON_RIGHT])
		env.game = delete_wall((size_t)env.editor.sel_wall, env.game);
	return (env);
}