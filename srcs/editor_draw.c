/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:12:48 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/23 13:36:47 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_vec2		screen_space(t_vec2 vec, t_editor editor)
{
	vec = vec2_scale(vec, editor.zoom);
	vec = vec2_add(vec, editor.offset);
	return (vec);
}

static void			draw_walls(t_game game, t_editor editor, t_color *buf)
{
	size_t	i;
	t_vec2	points[2];

	i = 0;
	while (i < game.nwalls)
	{
		points[0] = screen_space(game.points[game.walls[i].a], editor);
		points[1] = screen_space(game.points[game.walls[i].b], editor);
		bresenham(buf, (t_pix) {(int)points[0].u, (int)points[0].v},\
			(t_pix) {(int)points[1].u, (int)points[1].v},\
			(game.walls[i].portal >= 0) ? TRACTOR_R : WHITE);
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
		draw_point(vec2_to_fvec2(point), POINT_SIZE, buf,\
			(editor.sel_point == (long)i) ? UBE : LIBERTY);
		i++;
	}
	draw_physic(game.player.physic, editor, buf, MOONSTONE);
	draw_physic(game.player.spawn, editor, buf, MUSTARD);
}
