/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 11:25:08 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/03 17:48:30 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>

static void	minimap(t_fvec2 a, t_fvec2 b, t_color *buf)
{
	t_pix	pixes[2];

	pixes[0] = (t_pix) {
		f_to_int((a.u + f_from_int(10)) * 10),
		f_to_int((a.v + f_from_int(10)) * 10)
	};
	pixes[1] = (t_pix) {
		f_to_int((b.u + f_from_int(10)) * 10),
		f_to_int((b.v + f_from_int(10)) * 10)
	};
	bresenham(buf, pixes[0], pixes[1], RED);
	bresenham(buf, (t_pix) {95, 100}, (t_pix){105, 100}, GREEN);
	bresenham(buf, (t_pix) {100, 100}, (t_pix){100, 120}, GREEN);
}

static void	screen_space(t_fvec2 a, t_fvec2 b, t_fvec2 h, t_color *buf)
{
	t_pix	pixes[4];
	t_fixed	coef;

	minimap(a, b, buf);

	if (a.v > 0 || b.v > 0)
	{
		if (a.v <= 0)
		{
			coef = f_div(-b.v, a.v - b.v);
			a = (t_fvec2) {f_mul(coef, a.u - b.u) + b.u, 1000};
		}
		else if (b.v <= 0)
		{
			coef = f_div(-a.v, b.v - a.v);
			b = (t_fvec2) {f_mul(coef, b.u - a.u) + a.u, 1000};
		}
		pixes[0] = (t_pix) {
			WIDTH / 2 - f_to_int(f_mul(a.u, f_div(f_from_int(RATIO), a.v))),
			HEIGHT / 2 - f_to_int(f_div(f_from_int(RATIO) + h.v * 100, a.v))
		};
		pixes[1] = (t_pix) {
			WIDTH / 2 - f_to_int(f_mul(b.u, f_div(f_from_int(RATIO), b.v))),
			HEIGHT / 2 - f_to_int(f_div(f_from_int(RATIO) + h.v * 100, b.v))
		};
		pixes[2] = (t_pix) {
			WIDTH / 2 - f_to_int(f_mul(b.u, f_div(f_from_int(RATIO), b.v))),
			HEIGHT / 2 + f_to_int(f_div(f_from_int(RATIO) - h.u * 100, b.v))
		};
		pixes[3] = (t_pix) {
			WIDTH / 2 - f_to_int(f_mul(a.u, f_div(f_from_int(RATIO), a.v))),
			HEIGHT / 2 + f_to_int(f_div(f_from_int(RATIO) - h.u * 100, a.v))
		};
		bresenham(buf, pixes[0], pixes[1], WHITE);
		bresenham(buf, pixes[1], pixes[2], WHITE);
		bresenham(buf, pixes[2], pixes[3], WHITE);
		bresenham(buf, pixes[3], pixes[0], WHITE);
	}
}

static void		display_wall(t_wall wall, t_game game, t_vec2 h, t_color *buf)
{
	const t_vec2	*points = game.points;
	t_vec2			a;
	t_vec2			b;
	t_fvec2			a_f;
	t_fvec2			b_f;

	h = (t_vec2) {h.u - game.player.physic.pos.z, h.v - game.player.physic.pos.z};
	a = points[wall.a];
	b = points[wall.b];
	a = vec2_sub(a, vec3_to_vec2(game.player.physic.pos));
	b = vec2_sub(b, vec3_to_vec2(game.player.physic.pos));
	a = vec2_rot(a, -game.player.physic.look.u);
	b = vec2_rot(b, -game.player.physic.look.u);
	a_f = vec2_to_fvec2(a);
	b_f = vec2_to_fvec2(b);
	screen_space(a_f, b_f, vec2_to_fvec2(h), buf);
}

void			display_sector(t_sector sector, t_game game, t_color *buf)
{
	size_t	i;
	t_vec2	h;

	i = 0;
	while (i < sector.number && sector.start + i < game.nwalls)
	{
		h.u = sector.floor;
		h.v = sector.ceiling;
		display_wall(game.walls[sector.start + i], game, h, buf);
		i++;
	}
}