/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 11:21:46 by hugo              #+#    #+#             */
/*   Updated: 2019/06/04 14:54:52 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRESENHAM_H
# define BRESENHAM_H

# include <vec.h>
# include <graphic.h>

typedef struct	s_pix_fixed
{
	t_fixed	x;
	t_fixed	y;
}				t_pix_fixed;

typedef struct	s_bres
{
	t_pix_fixed	src;
	int			diff[2];
	int			inc[2];
}				t_bres;

void			bresenham(t_color *buff, t_pix a, t_pix b, t_color color);
void			dotted(t_color *buff, t_pix a, t_pix b, t_color color);

#endif
