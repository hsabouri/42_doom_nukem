/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _graphic_singletons.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 07:04:14 by hugo              #+#    #+#             */
/*   Updated: 2019/02/07 07:09:30 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GRAPHIC_SINGLETONS_H
# define _GRAPHIC_SINGLETONS_H

# include <vec.h>

/*
** This header contains all the singletons structures used to draw on screen
** in a highly optimized manner.
*/

typedef struct	s_last
{
	size_t	frame;
	int		x;
	int		start;
	int		end;
}				t_last;

typedef struct	s_i_wall
{
	size_t		wall_id;
	t_fvec2		a;
	t_fvec2		b;
}				t_i_wall;

#endif