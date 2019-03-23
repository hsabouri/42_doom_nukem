/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 12:02:38 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/23 15:37:25 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOT_H
# define ROOT_H

# include <editor.h>

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

t_component		init_root(t_env *env, t_sdl *sdl);

#endif