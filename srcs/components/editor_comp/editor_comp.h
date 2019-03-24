/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_comp.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:53:47 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/24 16:09:48 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_COMP_H
# define EDITOR_COMP_H

# include "../root.h"

typedef enum	e_editor_type
{
	MAP,
	MATERIAL,
	ENTITY,
	ACTION_EVENT
}				t_editor_type;

typedef struct	s_editor_root_state
{
	t_editor_type	type;
	t_env			*env;
}				t_editor_root_state;

t_component		init_editor_root(t_env *env, t_sdl *sdl);

#endif
