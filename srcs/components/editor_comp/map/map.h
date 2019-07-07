/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:53:47 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/07 16:48:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../editor_comp.h"

typedef struct		s_sector_color_tool
{
	t_env		*env;
	t_event		*events;
	ssize_t		*selected_wall;
	ssize_t		sector;
	t_color		*color;
}					t_sector_color_tool;

typedef struct		s_wall_tool
{
	ssize_t		*wall_points;
	ssize_t		*selected_point;
	ssize_t		*selected_wall;
	ssize_t		*unassigned_wall;
	t_event		*events;
}					t_wall_tool;

typedef struct		s_assign_entity
{
	ssize_t		*selected_entity;
	ssize_t		*selected_spawn;
	ssize_t		*selected_wall;
	ssize_t		*walls;
	ssize_t		*entity;
	ssize_t		*spawn;
	t_event		*events;
}					t_assign_entity;

typedef struct		s_entity_tool
{
	ssize_t		*selected_entity;
	ssize_t		*selected_spawn;
	ssize_t		*selected_class;
	t_event		*events;
}					t_entity_tool;

typedef struct		s_point_tool
{
	ssize_t		*selected_point;
	t_event		*events;
}					t_point_tool;

typedef enum		e_editor_map_mode
{
	CREATE_POINT,
	CREATE_WALL,
	ASSIGN_WALL,
	CREATE_PORTAL,
	TOOL_ENTITY,
	ASSIGN_ENTITY,
	MOVE,
	SECTOR_COLOR,
	ENTITY_DATA,
}					t_editor_map_mode;

typedef struct		s_editor_map_state
{
	t_vec2				offset;
	float				zoom;
	t_env				*env;
	int					grid_size;
	int					magnetisme;
	t_editor_map_mode	tool;
	ssize_t				selected_point;
	ssize_t				selected_wall;
	ssize_t				unassigned_wall;
	ssize_t				wall_points[2];
	ssize_t				selected_walls[2];
	ssize_t				selected_entity;
	ssize_t				selected_spawn;
	ssize_t				entity;
	ssize_t				spawn;
	ssize_t				selected_class;
}					t_editor_map_state;

typedef struct		s_assign_tool
{
	ssize_t				*walls;
	ssize_t				*selected_wall;
	ssize_t				*unassigned_wall;
	t_event				*events;
	t_editor_map_state	*parent;
}					t_assign_tool;

typedef struct		s_assign_portal_tool
{
	ssize_t				*walls;
	ssize_t				*selected_wall;
	t_event				*events;
	t_editor_map_state	*parent;
}					t_assign_portal_tool;

typedef struct		s_state_buf
{
	t_editor_map_state	state;
	t_color				*buf;
	t_color				color;
	int					modifier;
}					t_state_buf;

void				draw_map(t_editor_map_state state, t_color *buf);
void				foreach_wall(void *wall, void *param, size_t i);

t_component			init_editor_map(t_env *env, t_sdl *sdl);
int					grid_size(void *map_state);
int					map_editor_update(t_component *self, void *parent);
void				map_editor_render(const t_component self, t_color *buf);
t_array				index_childs_1(t_env *env, t_editor_map_state *state,
					t_sdl *sdl);
t_array				index_childs_2(t_env *env, t_editor_map_state *state,
					t_sdl *sdl, t_array ret);
t_array				index_childs_3(t_env *env, t_editor_map_state *state,
					t_sdl *sdl, t_array ret);
t_array				index_childs_4(t_env *env, t_editor_map_state *state,
					t_sdl *sdl, t_array ret);
t_array				index_childs_5(t_env *env, t_editor_map_state *state,
					t_sdl *sdl, t_array ret);

t_component			init_point_tool(t_env *env, ssize_t *selected, t_sdl *sdl);
t_component			init_wall_tool(t_env *env, t_editor_map_state *parent,
					t_sdl *sdl);
t_component			init_assign_tool(t_env *env, t_editor_map_state *parent,
					t_sdl *sdl);
t_component			init_assign_portal_tool(t_env *env,
					t_editor_map_state *parent, t_sdl *sdl);

t_component			init_entity_tool(t_env *env, t_editor_map_state *parent,
					t_sdl *sdl);
t_component			init_assign_entity(t_env *env, t_assign_entity v,
					t_sdl *sdl);
t_component			init_entity_data(t_env *env, t_assign_entity v,
					t_sdl *sdl);
t_component			init_entity_info(t_editor_map_state *state, t_sdl *sdl);

t_component			init_sector_color_tool(t_env *env,
					t_editor_map_state *parent, t_sdl *sdl);

t_vec2				screen_space(t_vec2 vec, t_editor_map_state state);
t_vec2				point_from_mouse(t_editor_map_state state, t_event events,
					int magnet);

float				capsule(t_vec2 a, t_vec2 b, t_vec2 p);
float				circle(t_vec2 a, t_vec2 p);
ssize_t				select_point(t_editor_map_state editor,
					ssize_t selected_point, t_event events);
ssize_t				select_wall(t_editor_map_state editor,
					ssize_t selected_wall, t_event events);
ssize_t				select_unassigned_wall(t_editor_map_state editor,
					ssize_t selected_wall, t_event events);
ssize_t				select_entity(t_editor_map_state editor,
					ssize_t selected_entity, t_event events, int spawn);
void				select_multi(ssize_t curr, ssize_t *dual, t_event events);

size_t				find_sector(size_t wall_id, t_game game);

void				draw_look(t_vec2 sp_pos, float angle, t_color color,
					t_state_buf state);

void				foreach_entity(void *entity, void *param, size_t i);
void				foreach_portal(void *port, void *param, size_t i);

t_component			create_list_class(t_env *env, t_sdl *sdl);

void				on_pointer(t_editor_map_state state, t_event events,
					t_color *buf);

#endif
