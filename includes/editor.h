/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:22:48 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/06 15:41:37 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include <doom.h>

# define MOVE_SPEED 5
# define ZOOM_SPEED 0.2
# define INITIAL_ZOOM 30
# define INITIAL_OFFSET_X 0
# define INITIAL_OFFSET_Y 0

# define POINT_SIZE 4
# define ENTITY_SIZE 3

# include <srcs/common/translate_id.h>

t_editor		init_editor(void);

t_game			create_point(t_vec2 pts, ssize_t index, t_game game);
t_game			create_wall(size_t uwall, size_t sector, t_game game);
t_game			create_portal(ssize_t wa, ssize_t wb, t_game game,
				int equalize);
t_game			create_sector(size_t start, size_t nwalls, t_game game);
t_game			create_material(size_t selected, t_game game);
t_game			create_entity(t_vec2 pos, size_t class_id, t_game game);

t_game			delete_portal(size_t portal, t_game game);
t_game			delete_sector(size_t sector, t_game game);
t_game			delete_wall(size_t wall, t_game game);
t_game			delete_point(size_t point, t_game game);
t_game			delete_entity(size_t entity, t_game game);
t_game			delete_material(size_t mat, t_game game);

t_selected		world_selector(t_game game);

t_game			del_update_walls(ssize_t pts, ssize_t portal, t_game game);
t_game			del_update_sectors(ssize_t wall, ssize_t sector, t_game game);
t_game			del_update_portals(ssize_t wall, ssize_t sector, t_game game);
t_game			del_update_inventory(ssize_t entity, t_game game);
t_game			del_update_entities(ssize_t sector, t_game game);

t_game			new_update_portals(ssize_t wall, ssize_t sector, t_game game);
t_game			new_update_walls(ssize_t point, ssize_t portal, t_game game);
t_game			new_update_sectors(ssize_t wall, ssize_t sector, t_game game);

t_game			del_mat_update_materials(size_t mat, size_t a_old, t_game game);
t_game			del_mat_update_walls(size_t mat, size_t a_old, t_game game);
t_game			del_mat_update_sectors(size_t mat, size_t a_old, t_game game);
t_game			del_mat_update_portals(size_t mat, size_t a_old, t_game game);
t_game			del_mat_update_multi_mats(size_t mat, size_t a_old,
				t_game game);

t_game			create_mat_update_materials(size_t a_old, t_game game);
t_game			create_mat_update_walls(size_t a_old, t_game game);
t_game			create_mat_update_sectors(size_t a_old, t_game game);
t_game			create_mat_update_portals(size_t a_old, t_game game);
t_game			create_mat_update_multi_mats(size_t a_old, t_game game);

void			legend(t_color *buf, t_sdl *sdl);
t_env			game_editing(t_env env, t_player player);

t_game			player_properties(t_game game, t_event events);

t_env			move_texture_tool(t_env env, t_selected selected);
t_env			move_material_tool(t_env env, t_selected selected);
t_env			scale_material_tool(t_env env, t_selected selected);
t_env			sector_height_tool(t_env env, t_selected selected);
t_env			change_material_tool(t_env env, t_selected selected);

#endif
