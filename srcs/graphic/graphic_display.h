/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_display.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:28:14 by hugo              #+#    #+#             */
/*   Updated: 2019/02/12 11:03:44 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_DISPLAY_H
# define GRAPHIC_DISPLAY_H

# include <stdlib.h>

typedef struct	s_last
{
	size_t	frame;
	int		x;
	int		start;
	int		end;
}				t_last;

#endif