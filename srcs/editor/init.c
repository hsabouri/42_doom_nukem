/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:39:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/26 18:37:18 by hsabouri         ###   ########.fr       */
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
	res.game_tools[0] = &move_texture_tool;
	res.game_tools[1] = &move_material_tool;
	res.game_tools[2] = &scale_material_tool;
	res.game_tools[3] = &sector_height_tool;
	res.game_tools[4] = &change_material_tool;
	return (res);
}
