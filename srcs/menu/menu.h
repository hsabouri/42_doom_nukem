/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:46:00 by iporsenn          #+#    #+#             */
/*   Updated: 2019/03/30 15:46:01 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include <doom.h>
# include "../components/common/common.h"

typedef	enum	e_menu_mode
{
	START_MODE,
	NEW_GAME,
	NEW_MAP
}				t_menu_mode;

typedef struct	s_menu_state
{
	t_env		*env;
	t_menu_mode	type;
}				t_menu_state;

t_array			init_start_menu(t_array childs, t_sdl *sdl,
				t_menu_state *state);
t_array			init_level_menu(t_array childs, t_sdl *sdl,
				t_menu_state *state);
int				new_map(void *parent_state);
int				new_game(void *parent_state);

#endif
