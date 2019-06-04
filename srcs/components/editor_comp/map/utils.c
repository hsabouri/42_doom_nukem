/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:05:55 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 14:34:23 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./map.h"

t_vec2		screen_space(t_vec2 vec, t_editor_map_state state)
{
	vec = vec2_scale(vec, state.zoom);
	vec = vec2_mult(vec, vec2_new(1, -1));
	vec = vec2_add(vec, state.offset);
	vec = vec2_add(vec, vec2_new(WIDTH / 2, -HEIGHT / 2));
	vec.v += HEIGHT;
	return (vec);
}

t_vec2		point_from_mouse(t_editor_map_state state, t_event events,
int magnet)
{
	t_vec2	new_point;

	new_point = (t_vec2) {events.x, events.y};
	new_point = vec2_sub(new_point, state.offset);
	new_point = vec2_sub(new_point, vec2_new(WIDTH / 2, -HEIGHT / 2));
	new_point.v -= HEIGHT;
	new_point.v *= -1;
	new_point = vec2_scale(new_point, 1 / state.zoom);
	if (magnet && state.grid_size)
	{
		new_point.u = roundf(new_point.u * state.grid_size) / state.grid_size;
		new_point.v = roundf(new_point.v * state.grid_size) / state.grid_size;
	}
	return (new_point);
}

float		capsule(t_vec2 a, t_vec2 b, t_vec2 p)
{
	const t_vec2	pa = vec2_sub(p, a);
	const t_vec2	ba = vec2_sub(b, a);
	const float		h = clamp(vec2_dot(pa, ba) / vec2_dot(ba, ba), 0.0, 1.0);

	return (1.0 / vec2_inv_size(vec2_sub(pa, vec2_scale(ba, h))));
}

float		circle(t_vec2 a, t_vec2 p)
{
	return (1 / vec2_inv_size(vec2_sub(a, p)));
}

size_t		find_sector(size_t wall_id, t_game game)
{
	size_t	i;

	i = 0;
	while (i < game.nsectors - 1)
	{
		if (game.sectors[i].start <= wall_id
			&& game.sectors[i + 1].start > wall_id)
			return (i);
		++i;
	}
	return (game.nsectors - 1);
}
