/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:27:41 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/19 18:27:48 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H
# include <doom.h>

# define A highest
# define B ((highest + 1) % 4)
# define C ((highest + 2) % 4)
# define D ((highest + 3) % 4)

/*
** This header contains all the structures used to draw on screen in an
** optimized manner.
*/

typedef struct		s_color
{
	u_int8_t	b;
	u_int8_t	g;
	u_int8_t	r;
	u_int8_t	a;
}					t_color;

typedef struct		s_pix
{
	int32_t	x;
	int32_t	y;
}					t_pix;

typedef struct		s_pix_fixed
{
	t_fixed	x;
	t_fixed	y;
}					t_pix_fixed;

typedef struct		s_order
{
	int	left[2];
	int	right[2];
}					t_order;

t_pix_fixed			from_pix(t_pix pixel);

#endif
