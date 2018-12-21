/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 11:25:08 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/21 15:07:52 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static void	screen_space(t_vec2 a, t_vec2 b, t_color *buf)
{
	t_pix_fixed		pixes[4];

	if (a.v > 0.000001 || b.v > 0.000001)
	{
		if (a.v < 0.000001)
			a = (t_vec2) {(-b.v) / (a.v - b.v) * (a.u - b.u) + b.u, 0.001, 1};
		else if (b.v < 0.000001)
			b = (t_vec2) {(-a.v) / (b.v - a.v) * (b.u - a.u) + a.u, 0.001, 1};
		pixes[0] = (t_pix_fixed) { f_from_float(a.u * (180 / a.v) + WIDTH / 2),
			f_from_float(HEIGHT / 2 + 180 / a.v)};
		pixes[1] = (t_pix_fixed) { f_from_float(b.u * (180 / b.v) + WIDTH / 2),
			f_from_float(HEIGHT / 2 + 180 / b.v)};
		pixes[2] = (t_pix_fixed) { f_from_float(b.u * (180 / b.v) + WIDTH / 2),
			f_from_float(HEIGHT / 2 - 180 / b.v)};
		pixes[3] = (t_pix_fixed) { f_from_float(a.u * (180 / a.v) + WIDTH / 2),
			f_from_float(HEIGHT / 2 - 180 / a.v)};
		quad(buf, pixes, RED);
	}
}

void		display_wall(void *wall, void *game)
{
	const t_array	points = ((t_game *)game)->points;
	t_vec2			a;
	t_vec2			b;

	a = *((t_vec2 *)anth(&points, ((t_wall *)wall)->a));
	b = *((t_vec2 *)anth(&points, ((t_wall *)wall)->b));
	a = vec2_sub(a, vec3_to_vec2(((t_game *)game)->player.ph_enabled.pos));
	b = vec2_sub(b, vec3_to_vec2(((t_game *)game)->player.ph_enabled.pos));
	a = vec2_rot(a, -((t_game *)game)->player.ph_enabled.look.u);
	b = vec2_rot(b, -((t_game *)game)->player.ph_enabled.look.u);
	screen_space(a, b, ((t_game *)game)->current_buffer);
}
