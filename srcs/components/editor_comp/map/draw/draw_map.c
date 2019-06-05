/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:12:48 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 14:41:30 by hsabouri         ###   ########.fr       */
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
			current = vec2_new((int)(x - ((state.offset.u + WIDTH / 2)
				/ state.zoom) * state.grid_size), (int)(y + ((state.offset.v
				- HEIGHT / 2) / state.zoom) * state.grid_size));
			current = vec2_scale(current, grid);
			current = screen_space(current, state);
			current = vec2_add(current, vec2_new(1, 1));
			draw_point(vec2_to_fvec2(current), 1, buf, GREY);
			y++;
		}
		x++;
	}
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
	p = vec2_add(p, vec2_new(1, 1));
	color = state->color;
	if ((size_t)state->state.selected_point == i)
	{
		color.r += 30;
		color.g += 30;
		color.b += 30;
	}
	if ((size_t)state->state.wall_points[0] == i
		|| (size_t)state->state.wall_points[1] == i)
		color = ORANGE;
	draw_point(vec2_to_fvec2(p), size, state->buf, color);
}

static void			draw_entities(t_editor_map_state *state,
t_state_buf state_buf)
{
	t_game				game;
	t_array				tmp_array;

	game = state->env->game;
	tmp_array = anew(game.entities, game.nentities, sizeof(t_entity));
	state_buf.color = E_DAMAGE;
	aforeachi_state(&tmp_array, &foreach_entity, &state_buf);
	state_buf.color = E_PLAYER;
	foreach_entity(&game.player.my_entity, &state_buf, game.nentities);
}

void				draw_map(t_editor_map_state state, t_color *buf)
{
	t_game				game;
	t_state_buf			state_buf;
	t_array				tmp_array;

	game = state.env->game;
	if (state.grid_size)
		grid(state, buf);
	state_buf = (t_state_buf) {state, buf, WHITE, 0};
	tmp_array = anew(game.walls, game.nwalls, sizeof(t_wall));
	state_buf.modifier = 0;
	aforeachi_state(&tmp_array, &foreach_wall, &state_buf);
	state_buf.color = ORANGE;
	state_buf.modifier = 1;
	tmp_array = anew(&game.walls[game.nwalls], game.nuwalls, sizeof(t_wall));
	aforeachi_state(&tmp_array, &foreach_wall, &state_buf);
	state_buf.color = LIBERTY;
	tmp_array = anew(game.points, game.npoints, sizeof(t_vec2));
	aforeachi_state(&tmp_array, &foreach_point, &state_buf);
	draw_entities(&state, state_buf);
	if (state.tool == CREATE_PORTAL)
	{
		tmp_array = anew(game.portals, game.nportals, sizeof(t_portal));
		aforeachi_state(&tmp_array, &foreach_portal, (void *)&state_buf);
	}
	on_pointer(state, state.env->events, buf);
}
