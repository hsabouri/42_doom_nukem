/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:12:48 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/27 12:18:54 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.h"

static void			grid(t_editor_map_state state, t_color *buf)
{
	int			n;
	int			x;
	int			y;
	t_vec2		current;
	const float	grid = 1.0 / state.grid_size;

	if ((n = ((HEIGHT * 1.1 * state.grid_size) / state.zoom)) > 100)
		return ;
	x = 0;
	while (x < n * ((float)WIDTH / HEIGHT))
	{
		y = 0;
		while (y < n)
		{
			current = vec2_new(
				(int)(x - (state.offset.u / state.zoom) * state.grid_size) - 1,
				(int)(y + (state.offset.v / state.zoom) * state.grid_size));
			current = vec2_scale(current, grid);
			current = screen_space(current, state);
			draw_point(vec2_to_fvec2(current), 1, buf, GREY);
			y++;
		}
		x++;
	}
}

static void			foreach_wall(void *wall, void *param, size_t i)
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
	if (state.state.tool == ASSIGN_WALL || state.state.tool == CREATE_WALL ||
		state.state.tool == CREATE_PORTAL)
	{
		state.color.r /= 2;
		state.color.g /= 2;
		state.color.b /= 2;
	}
	if (state.state.tool == CREATE_PORTAL &&
		i == (size_t)state.state.selected_walls[0])
		bresenham(state.buf, a_p, b_p, PORTAL_B);
	else if (state.state.tool == CREATE_PORTAL &&
		i == (size_t)state.state.selected_walls[1])
		bresenham(state.buf, a_p, b_p, PORTAL_O);
	else if ((i == (size_t)state.state.selected_wall ||
		i == (size_t)state.state.selected_walls[1]) && !state.modifier)
		bresenham(state.buf, a_p, b_p, WHITE);
	else if ((i == (size_t)state.state.unassigned_wall ||
		i == (size_t)state.state.selected_walls[0]) && state.modifier)
		bresenham(state.buf, a_p, b_p, MUSTARD);
	else if (((t_wall *)wall)->portal >= 0)
		bresenham(state.buf, a_p, b_p, RED);
	else
		bresenham(state.buf, a_p, b_p, state.color);
}

static void			foreach_point(void *point, void *param, size_t i)
{
	const t_state_buf	*state = ((t_state_buf *)param);
	t_vec2				p;
	int					size;
	t_color				color;
	
	size = (state->state.zoom < 10) ? 2 : 4;
	size = (state->state.zoom > 60) ? 6 : size;
	p = *(t_vec2 *)point;
	p = screen_space(p, state->state);
	color = state->color;
	if ((size_t)state->state.selected_point == i)
	{
		color.r += 30;
		color.g += 30;
		color.b += 30;
	}
	if ((size_t)state->state.wall_points[0] == i ||
		(size_t)state->state.wall_points[1] == i)
		color = ORANGE;
	draw_point(vec2_to_fvec2(p), size, state->buf, color);
}

void				draw_map(t_editor_map_state state, t_color *buf)
{
	t_state_buf			state_buf;
	t_array				tmp_array;
	
	if (state.grid_size)
		grid(state, buf);
	state_buf = (t_state_buf) {state, buf, WHITE, 0};
	tmp_array = anew(state.env->game.walls, state.env->game.nwalls, sizeof(t_wall));
	state_buf.modifier = 0;
	aforeachi_state(&tmp_array, &foreach_wall, (void *)&state_buf);
	state_buf.color = ORANGE;
	state_buf.modifier = 1;
	tmp_array = anew(&state.env->game.walls[state.env->game.nwalls],
		state.env->game.nuwalls, sizeof(t_wall));
	aforeachi_state(&tmp_array, &foreach_wall, (void *)&state_buf);
	state_buf.color = LIBERTY;
	tmp_array = anew(state.env->game.points, state.env->game.npoints, sizeof(t_vec2));
	aforeachi_state(&tmp_array, &foreach_point, (void *)&state_buf);
	tmp_array = anew(state.env->game.entities, state.env->game.nentities,
		sizeof(t_entity));
	aforeachi_state(&tmp_array, &foreach_entity, (void *)&state_buf);
	if (state.tool == CREATE_PORTAL)
	{
		tmp_array = anew(state.env->game.portals, state.env->game.nportals, sizeof(t_portal));
		aforeachi_state(&tmp_array, &foreach_portal, (void *)&state_buf);
	}
}
