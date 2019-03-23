/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:53:47 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/23 15:37:15 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../root.h"

typedef struct	s_editor_map_state
{
	t_array	unassigned_walls;
	t_vec2	offset;
	float	zoom;
	t_game	*game;
	int		grid_size;
}				t_editor_map_state;

typedef struct	s_state_buf
{
	t_editor_map_state	state;
	t_color				*buf;
	t_color				color;
}				t_state_buf;


void			draw_map(t_editor_map_state state, t_color *buf);
t_component		init_editor_map(t_env *env, t_sdl *sdl);
t_component		init_editor_root(t_env *env, t_sdl *sdl);

#endif
