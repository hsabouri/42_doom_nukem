/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:28:14 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/19 12:14:17 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.h"

void			on_pointer(t_editor_map_state state, t_event events,
t_color *buf)
{
	const t_vec2	real = point_from_mouse(state, events, state.magnetisme);
	const t_vec2	s = screen_space(real, state);

	if (state.tool != ASSIGN_ENTITY && state.tool != ASSIGN_WALL
		&& state.tool != CREATE_PORTAL && state.tool != ENTITY_DATA)
	{
		bresenham(buf, (t_pix) {s.u - 20, s.v},
			(t_pix) {s.u + 20, s.v}, MOONSTONE);
		bresenham(buf, (t_pix) {s.u, s.v - 20},
			(t_pix) {s.u, s.v + 20}, MOONSTONE);
	}
}
