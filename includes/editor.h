/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:22:48 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/16 11:27:32 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include <doom.h>

# define MOVE_SPEED 5
# define ZOOM_SPEED 0.2

# define POINT_SIZE 4
# define ENTITY_SIZE 3

# include <srcs/common/translate_id.h>

t_editor		init_editor(void);

void			draw_map(t_game game, t_editor editor, t_color *buf);

t_game			create_point(t_vec2 pts, ssize_t index, t_game game);
t_game			create_wall(ssize_t pts[2], int new_sector, t_game game);
t_game			create_portal(ssize_t wa, ssize_t wb, t_game game);
t_game			create_sector(size_t start, size_t nwalls, t_game game);

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

void			display_text(t_sdl *sdl);

t_vec2			point_from_mouse(t_event events, t_editor editor);
ssize_t			select_point(t_game game, t_editor editor,\
				t_event events);
ssize_t			select_wall(t_game game, t_editor editor,\
				t_event events);
t_editor		select_multi_points(t_editor editor,\
				t_event events, ssize_t point);
void			legend(t_color *buf, t_sdl *sdl);
t_env			game_editing(t_env env, t_player player);
t_game			player_properties(t_game game, t_event events);

t_env			point_tool(t_env env);
t_env			wall_tool(t_env env);
t_env			portal_tool(t_env env);

t_env			move_texture_tool(t_env env, t_selected selected);
t_env			move_material_tool(t_env env, t_selected selected);
t_env			scale_material_tool(t_env env, t_selected selected);
t_env			sector_height_tool(t_env env, t_selected selected);
t_env			change_material_tool(t_env env, t_selected selected);

#endif
