/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:00:53 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/04 16:25:10 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SINGLETONS_H
# define SINGLETONS_H

# include <graphic.h>
# include <doom.h>
# include "srcs/graphic/multi_sprite.h"

typedef struct		s_bunch_entity_compute
{
	t_game			game;
	t_context		context;
	t_limit			limit;
	t_cache_entity	*entities;
	t_fvec2			pos;
	size_t			i;
	int				*nentities;
}					t_bunch_entity_compute;

typedef struct		s_bunch_compute
{
	t_game			game;
	t_context		context;
	t_limit			limit;
	t_cache_wall	*walls;
	t_fvec2			pos;
	size_t			i;
	int				*nwalls;
}					t_bunch_compute;

#endif
