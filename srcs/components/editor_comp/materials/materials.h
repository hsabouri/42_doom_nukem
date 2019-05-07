/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/07 15:46:40 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "../editor_comp.h"

typedef struct	s_editor_mat_state
{
	t_color	*selected_filter;
	t_color	*selected_color;
	size_t	selected;
	t_env	*env;
}				t_editor_mat_state;

void			render_preview(t_mat mat, int width, int height, t_color *buf);

t_component		init_editor_mat(t_env *env, t_sdl *sdl);
t_component		create_list_materials(t_env *env, t_sdl *sdl);
t_component		init_preview(t_editor_mat_state *parent, t_sdl *sdl);

t_component		init_color_chooser(t_env *env, t_color **to_change,
				t_pix pos, t_sdl *sdl);

#endif