/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:46:52 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/24 16:02:10 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

#include <editor.h>

typedef struct	s_button_state
{
	t_event *events;
	int		*to_activate;
	int		active_value;
	t_color	background;
}				t_button_state;

typedef struct	s_button
{
	t_pix		pos;
	t_pix		size;
	t_color		background;
	t_event		*events;
	char		*place_holder;
	int			*to_activate;
	int			active_value;
	t_img		img;
} 				t_button;

t_component		init_button(t_button button, t_sdl *sdl);

#endif