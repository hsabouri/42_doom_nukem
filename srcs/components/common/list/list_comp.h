/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_comp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:23:28 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/09 15:37:49 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_COMP_H
# define LIST_COMP_H

# include "../common.h"

typedef struct	s_list_content
{
	t_img		img;
	char		text[28];
}				t_list_content;

typedef struct	s_list_state
{
	t_array		(*build)(void *parent);
	int			(*del)(void *parent, size_t i);
	int			(*add)(void *parent);
	int			(*select)(void *parent, size_t i);
	t_event		*events;
	t_color		bg;
	int			need_update;
	void		*parent;
	t_sdl		*sdl;
	int			y_scroll;
	int			destroy_image;
}				t_list_state;

typedef struct	s_list_comp
{
	t_array		(*build)(void *parent);
	int			(*del)(void *parent, size_t i);
	int			(*add)(void *parent);
	int			(*select)(void *parent, size_t i);
	char		*title;
	t_event		*events;
	t_color		bg;
	t_pix		pos;
	t_pix		size;
	int			destroy_image;
}				t_list_comp;

typedef struct	s_list_button_state
{
	size_t			i;
	int				(*del)(void *parent, size_t i);
	int				(*select)(void *parent, size_t i);
	int				is_active;
	t_event			*events;
	void			*parent;
	t_list_state 	*list;
	t_color			bg;
	t_pix			d_pos;
	int				*y_scroll;
	int			destroy_image;
}				t_list_button_state;

typedef struct	s_list_button
{
	size_t		i;
	void		*parent;
	t_pix		pos;
	t_pix		size;
	t_img		img;
	char		text[28];
	int			*y_scroll;
	int			destroy_image;
}				t_list_button;

t_component		init_list_comp(t_list_comp list, t_sdl *sdl);
t_component		init_list_button(t_list_button button, t_list_state state,
				t_sdl *sdl);

#endif