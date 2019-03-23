/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:22:31 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/23 15:35:46 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

# include "../root.h"

typedef struct	s_hud_state
{
	int yolo;
}				t_hud_state;

t_component		init_hud_root(t_env *env, t_sdl *sdl);

#endif