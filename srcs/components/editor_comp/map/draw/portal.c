/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:19:02 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/03 16:53:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.h"

static t_vec2	portal_pos(size_t wall, t_game game)
{
	const t_vec2	a = game.points[game.walls[wall].a];
	const t_vec2	b = game.points[game.walls[wall].b];
	const t_vec2	diff = vec2_sub(a, b);

	return (vec2_sub(a, vec2_scale(diff, 0.5)));
}

void			foreach_portal(void *port, void *param, size_t i)
{
	t_vec2				a;
	t_vec2				b;
	const t_state_buf	*state = ((t_state_buf *)param);
	const t_portal		portal = *(t_portal *)port;
	const t_game		game = state->state.env->game;

	(void)i;
	a = screen_space(portal_pos(portal.from_wall, game), state->state);
	b = screen_space(portal_pos(portal.to_wall, game), state->state);
	dotted(state->buf, (t_pix) {a.u, a.v}, (t_pix) {b.u, b.v}, LOW_R);
}
