/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:44:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/05 16:24:01 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "../editor_comp.h"

typedef struct	s_editor_mat_state
{
	size_t	selected;
	t_env	*env;
}				t_editor_mat_state;

void			render_preview(t_mat mat, int width, int height, t_color *buf);

t_component		init_editor_mat(t_env *env, t_sdl *sdl);
t_component		create_list_materials(t_env *env, t_sdl *sdl);
t_component		init_preview(t_editor_mat_state *parent, t_sdl *sdl);

#endif