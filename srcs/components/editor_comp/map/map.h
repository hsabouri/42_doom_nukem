/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:53:47 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/24 16:07:57 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../editor_comp.h"

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

#endif
