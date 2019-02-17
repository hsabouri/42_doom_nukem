/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:22:48 by hsabouri          #+#    #+#             */
/*   Updated: 2019/02/17 11:17:30 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include <structure.h>

# define MOVE_SPEED 5
# define ZOOM_SPEED 0.2

# define POINT_SIZE 4
# define ENTITY_SIZE 3

# include <srcs/common/translate_id.h>

typedef enum	e_tool
{
	POINT,
	WALL,
	PORTAL
}				t_tool;

typedef struct	s_editor
{
	int			enabled;
	float		zoom;
	t_vec2		offset;
	t_tool		tool;
	ssize_t		sel_point;
	ssize_t		sel_wall;
	ssize_t		points_wall[2];
	int			selecting;
}				t_editor;

t_editor		init_editor(void);

void			draw_map(t_game game, t_editor editor, t_color *buf);

t_sector		sector_height(t_game game, t_sector sector, t_part part,\
				float add);

t_game			create_point(t_vec2 pts, t_game game);
t_game			create_wall(ssize_t pts[2], int new_sector, t_game game);
t_game			create_portal(ssize_t wa, ssize_t wb, t_game game);

t_game			delete_portal(size_t portal, t_game game);
t_game			delete_sector(size_t sector, t_game game);
t_game			delete_wall(size_t wall, t_game game);
t_game			delete_point(size_t point, t_game game);

t_selected		world_selector(t_game game);

t_game			del_update_walls(ssize_t pts, ssize_t portal, ssize_t mat,\
				t_game game);
t_game			del_update_sectors(ssize_t wall, ssize_t mat, ssize_t sector,\
				t_game game);
t_game			del_update_portals(ssize_t wall, ssize_t sector, t_game game);
t_game			new_update_portals(ssize_t point, ssize_t wall, ssize_t sector,\
				t_game game);
t_game			new_update_walls(ssize_t point, ssize_t mat, ssize_t portal,\
				t_game game);
t_game			new_update_sectors(ssize_t wall, ssize_t mat, ssize_t sector,\
				t_game game);

#endif
