/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:53:47 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/27 14:48:53 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../editor_comp.h"

typedef struct	s_point_tool
{
	ssize_t		*selected_point;
	t_event		*events;
}				t_point_tool;

typedef enum	e_editor_map_mode
{
	CREATE_POINT,
	CREATE_WALL,
	ASSIGN_WALL,
	CREATE_PORTAL,
	MOVE,
	// More to come
}				t_editor_map_mode;

typedef struct	s_editor_map_state
{
	t_array				unassigned_walls;
	t_vec2				offset;
	float				zoom;
	t_env				*env;
	int					grid_size;
	int					magnetisme;
	t_editor_map_mode	tool;
	ssize_t				selected_point;
}				t_editor_map_state;

typedef struct	s_state_buf
{
	t_editor_map_state	state;
	t_color				*buf;
	t_color				color;
}				t_state_buf;

void			draw_map(t_editor_map_state state, t_color *buf);
t_component		init_editor_map(t_env *env, t_sdl *sdl);
t_component		init_point_tool(t_env *env, ssize_t *selected, t_sdl *sdl);
t_vec2			screen_space(t_vec2 vec, t_editor_map_state state);
t_vec2			point_from_mouse(t_editor_map_state state, t_event events,
				int magnet);

float			capsule(t_vec2 a, t_vec2 b, t_vec2 p);
float			circle(t_vec2 a, t_vec2 p);

#endif
