/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:12:48 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/09 16:22:53 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

static t_vec2		screen_space(t_vec2 vec, t_editor editor)
{
	vec = vec2_scale(vec, editor.zoom);
	vec = vec2_mult(vec, vec2_new(1, -1));
	vec = vec2_add(vec, editor.offset);
	vec.v += HEIGHT;
	return (vec);
}

static void			draw_walls(t_game game, t_editor editor, t_color *buf)
{
	size_t	i;
	t_vec2	pts[2];
	t_wall	wall;

	i = 0;
	while (i < game.nwalls)
	{
		wall = game.walls[i];
		pts[0] = screen_space(game.points[wall.a], editor);
		pts[1] = screen_space(game.points[wall.b], editor);
		if (i == (size_t)editor.sel_wall || editor.current_tool == POINT)
			bresenham(buf, (t_pix) {(int)pts[0].u, (int)pts[0].v},\
				(t_pix) {(int)pts[1].u, (int)pts[1].v},\
				(wall.portal >= 0) ? TRACTOR_R : WHITE);
		else
			bresenham(buf, (t_pix) {(int)pts[0].u, (int)pts[0].v},\
				(t_pix) {(int)pts[1].u, (int)pts[1].v},\
				(wall.portal >= 0) ? LOW_R : GREY);
		i++;
	}
}

static void			draw_physic(t_ph ph, t_editor editor, t_color *buf,
t_color color)
{
	t_vec2	points[2];

	points[0] = screen_space(vec3_to_vec2(ph.pos), editor);
	points[1] = vec2_add(vec2_rot((t_vec2) {0, 20}, ph.look_h), points[0]);
	draw_point(vec2_to_fvec2(points[0]), ENTITY_SIZE, buf, color);
	bresenham(buf, (t_pix) {points[0].u, points[0].v},
		(t_pix) {points[1].u, points[1].v}, color);
}

void				draw_map(t_game game, t_editor editor, t_color *buf)
{
	size_t	i;
	t_vec2	point;

	draw_walls(game, editor, buf);
	i = 0;
	while (i < game.npoints)
	{
		point = screen_space(game.points[i], editor);
		if (editor.current_tool == WALL && (editor.points_wall[0] == (long)i ||\
		editor.points_wall[1] == (long)i))
			draw_point(vec2_to_fvec2(point), POINT_SIZE, buf, RED);
		else if (editor.sel_point == (long)i)
			draw_point(vec2_to_fvec2(point), POINT_SIZE, buf, UBE);
		else
			draw_point(vec2_to_fvec2(point), POINT_SIZE, buf, LIBERTY);
		i++;
	}
	draw_physic(game.player.physic, editor, buf, MOONSTONE);
	draw_physic(game.player.spawn, editor, buf, MUSTARD);
}
