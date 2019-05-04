/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 12:20:12 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/03 18:23:05 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map.h"

void		draw_look(t_vec2 sp_pos, float angle, t_color color,
t_state_buf state)
{
	t_vec2		sp_pos2;
	int			size;
	t_pix		a;
	t_pix		b;


	size = state.state.zoom / 2;
	sp_pos2 = vec2_rot(vec2_new(0, -size), angle);
	sp_pos2 = vec2_add(sp_pos, sp_pos2);
	a = (t_pix) {sp_pos.u - 1, sp_pos.v - 1};
	b = (t_pix) {sp_pos2.u - 1, sp_pos2.v - 1};
	bresenham(state.buf, a, b, color);
}

static void	display_pos(t_entity entity, int size, t_color c,
const t_state_buf state)
{
	const t_vec2	pos = screen_space(vec3_to_vec2(entity.physic.pos),
		state.state);
	const t_vec2	spw = screen_space(vec3_to_vec2(entity.spawn.pos),
		state.state);

	c = (t_color) {c.r + 64, c.g + 64, c.b + 64, c.a};
	if (state.state.tool == TOOL_ENTITY || state.state.tool == ASSIGN_ENTITY)
		dotted(state.buf, (t_pix) {pos.u, pos.v}, (t_pix) {spw.u, spw.v}, c);
	draw_look(spw, entity.spawn.look_h, c, state);
	draw_point(vec2_to_fvec2(spw), size, state.buf, c);
	c = (t_color) {c.r - 64, c.g - 64, c.b - 64, c.a};
	draw_look(pos, entity.physic.look_h, c, state);
	draw_point(vec2_to_fvec2(pos), size, state.buf, c);
}

void		foreach_entity(void *entity, void *param, size_t i)
{
	const t_state_buf	*state = ((t_state_buf *)param);
	const t_entity		*e = (t_entity *)entity;
	int					size;
	t_color				c;
	
	size = (state->state.zoom < 10) ? 2 : 4;
	size = (state->state.zoom > 60) ? 6 : size;
	c = (e->damage) ? state->color : E_PEACEFUL;
	if ((size_t)state->state.selected_entity == i ||
		(size_t)state->state.selected_spawn == i ||
		(size_t)state->state.entity == i ||
		(size_t)state->state.spawn == i)
		c = (t_color) {c.r + 30, c.g + 30, c.b + 30, c.a};
	display_pos(*e, size, c, *state);
}
