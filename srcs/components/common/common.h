/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:46:52 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/22 16:10:21 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <editor.h>
# include "./list/list_comp.h"

typedef struct	s_button_ft_state
{
	t_event *events;
	int		**to_activate;
	int		active_value;
	int		is_active;
	t_color	background;
	int		scancode;
	t_img	img_active;
}				t_button_ft_state;

typedef struct	s_button_state
{
	t_event *events;
	int		*to_activate;
	int		active_value;
	int		is_active;
	t_color	background;
	int		scancode;
	t_img	img_active;
}				t_button_state;

typedef struct	s_cb_button_state
{
	t_event *events;
	t_color	background;
	int		is_active;
	int		(*callback)(void *parent_state);
	int		scancode;
	t_img	img_active;
}				t_cb_button_state;

typedef struct	s_switch_button_state
{
	t_event *events;
	int		*to_activate;
	int		enable_value;
	int		disable_value;
	t_color	background;
	int		scancode;
}				t_sw_button_state;

typedef struct	s_button_ft
{
	t_pix		pos;
	t_pix		size;
	t_color		background;
	t_event		*events;
	int			scancode;
	char		*place_holder;
	int			**to_activate;
	int			active_value;
	t_img		img;
	t_img		img_active;
}				t_button_ft;

typedef struct	s_button
{
	t_pix		pos;
	t_pix		size;
	t_color		background;
	t_event		*events;
	int			scancode;
	char		*place_holder;
	int			*to_activate;
	int			active_value;
	t_img		img;
	t_img		img_active;
}				t_button;

typedef struct	s_cb_button
{
	t_pix	pos;
	t_pix	size;
	t_color	background;
	t_event	*events;
	char	*place_holder;
	int		(*callback)(void *parent_state);
	t_img	img;
	int		scancode;
	t_img	img_active;
}				t_cb_button;

typedef struct	s_switch_button
{
	t_pix		pos;
	t_pix		size;
	t_color		background;
	t_event		*events;
	int			scancode;
	char		*place_holder;
	int			*to_activate;
	int			enable_value;
	int			disable_value;
	t_img		img;
}				t_sw_button;

typedef struct	s_display_deco_state
{
	int		*to_look_at;
	int		display_value;
	void	*state;
	int		invert;
}				t_display_deco_state;

typedef struct	s_help_component
{
	t_img	img;
}				t_help_state;

t_component		init_button(t_button button, t_sdl *sdl);
t_component		init_button_ft(t_button_ft button, t_sdl *sdl);
t_component		init_cb_button(t_cb_button button, t_sdl *sdl);
t_component		init_sw_button(t_sw_button button, t_sdl *sdl);
t_component		init_display_deco(t_display_deco_state deco, t_component child);
t_component		init_help_component(t_help_state state, t_sdl *sdl);
t_component		init_simple_text(const char *s, t_pix pos, t_sdl *sdl);
t_component		init_simple_rectangle(t_pix pos, t_pix size,
				t_color background, t_sdl *sdl);

void			destroy_button(t_component *self);
void			destroy_button_ft(t_component *self);
void			destroy_cb_button(t_component *self);

#endif
