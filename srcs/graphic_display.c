/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 11:25:08 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/29 16:11:56 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static void	screen_space(t_vec2 a, t_vec2 b, t_color *buf)
{
	t_pix	pixes[4];
	float	coef;

	if (a.v > FLT_EPSILON || b.v > FLT_EPSILON)
	{
		// printf("	-> a: {%f,	%f}		b: {%f,	%f}\n", a.u, a.v, b.u, b.v);
		if (a.v < FLT_EPSILON)
		{
			coef = (-b.v) / (a.v - b.v);
			a = (t_vec2) {coef * (a.u - b.u) + b.u, 0.001};
		}
		else if (b.v < FLT_EPSILON)
		{
			coef = (-a.v) / (b.v - a.v);
			b = (t_vec2) {coef * (b.u - a.u) + a.u, 0.001};
		}
		// printf("	   a: {%f,	%f}		b: {%f,	%f}\n", a.u, a.v, b.u, b.v);
		pixes[0] = (t_pix) {
			(int)(a.u * (180 / a.v) + WIDTH / 2),
			(int)(HEIGHT / 2 + 180 / a.v)};
		pixes[1] = (t_pix) {
			(int)(b.u * (180 / b.v) + WIDTH / 2),
			(int)(HEIGHT / 2 + 180 / b.v)};
		pixes[2] = (t_pix) {
			(int)(b.u * (180 / b.v) + WIDTH / 2),
			(int)(HEIGHT / 2 - 180 / b.v)};
		pixes[3] = (t_pix) {
			(int)(a.u * (180 / a.v) + WIDTH / 2),
			(int)(HEIGHT / 2 - 180 / a.v)};
		bresenham(buf, pixes[0], pixes[1], WHITE);
		bresenham(buf, pixes[1], pixes[2], WHITE);
		bresenham(buf, pixes[2], pixes[3], WHITE);
		bresenham(buf, pixes[3], pixes[0], WHITE);
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
