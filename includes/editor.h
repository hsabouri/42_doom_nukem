/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:22:48 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/07 11:07:17 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include <structure.h>

# define MOVE_SPEED 5
# define ZOOM_SPEED 0.2

# define POINT_SIZE 4
# define ENTITY_SIZE 3

typedef struct	s_component
{
	char	hover;
	char	focus;
	t_pix	position;
	t_pix	size;
	t_color	color;
	t_color	hlcolor;
}				t_component;

typedef struct	s_editor
{
	float		zoom;
	t_vec2		offset;
	long		sel_point;
	int			selecting;
	t_component	*components;
}				t_editor;

t_editor		init_editor(void);

void			draw_map(t_game game, t_editor editor, t_color *buf);

#endif
