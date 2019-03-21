/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:39:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/21 16:21:43 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_editor		init_editor(void)
{
	t_editor res;
	res = (t_editor) {
		.zoom = 25.0,
		.offset = (t_vec2) {0.0, 0.0},
		.sel_point = -1,
		.enabled = 0,
		.current_tool = POINT,
		.depth = 0,
		.game_tool = TOOL_NO};
	res.points_wall[0] = -1;
	res.points_wall[1] = -1;
	res.tools[0] = &point_tool;
	res.tools[1] = &wall_tool;
	res.tools[2] = &portal_tool;
	res.game_tools[0] = &move_texture_tool;
	res.game_tools[1] = &move_material_tool;
	return (res);
}