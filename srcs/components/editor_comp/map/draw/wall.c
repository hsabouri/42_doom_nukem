/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 16:29:34 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/19 12:14:56 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.h"

static t_color		get_color(t_editor_map_mode tool, size_t i,
t_state_buf state, t_wall wall)
{
	t_color color;

	if (tool == ASSIGN_WALL || tool == CREATE_PORTAL || tool == CREATE_WALL
		|| tool == ASSIGN_ENTITY || tool == SECTOR_COLOR || tool == ENTITY_DATA)
		state.color = (t_color) {state.color.r / 2,
			state.color.g / 2, state.color.b / 2, state.color.a};
	if (state.state.tool == CREATE_PORTAL
		&& i == (size_t)state.state.selected_walls[0])
		color = PORTAL_B;
	else if (state.state.tool == CREATE_PORTAL
		&& i == (size_t)state.state.selected_walls[1])
		color = PORTAL_O;
	else if ((i == (size_t)state.state.selected_wall
		|| i == (size_t)state.state.selected_walls[1]) && !state.modifier)
		color = WHITE;
	else if ((i == (size_t)state.state.unassigned_wall
		|| i == (size_t)state.state.selected_walls[0]) && state.modifier)
		color = MUSTARD;
	else if (wall.portal >= 0)
		color = RED;
	else
		color = state.color;
	return (color);
}

void				foreach_wall(void *wall, void *param, size_t i)
{
	t_vec2				a;
	t_vec2				b;
	t_pix				a_p;
	t_pix				b_p;
	t_state_buf			state;

	state = *((t_state_buf *)param);
	a = state.state.env->game.points[((t_wall *)wall)->a];
	b = state.state.env->game.points[((t_wall *)wall)->b];
	a = screen_space(a, state.state);
	b = screen_space(b, state.state);
	a_p.x = a.u;
	a_p.y = a.v;
	b_p.x = b.u;
	b_p.y = b.v;
	bresenham(state.buf, a_p, b_p, get_color(state.state.tool, i,
		state, *(t_wall *)wall));
}
