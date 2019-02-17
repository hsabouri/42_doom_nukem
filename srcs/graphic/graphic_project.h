/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_project.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 07:10:48 by hugo              #+#    #+#             */
/*   Updated: 2019/02/15 12:11:57 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_PROJECT_H
# define GRAPHIC_PROJECT_H

# include <vec.h>

typedef struct	s_hit
{
	ssize_t		wall;
	t_fvec2		ray;
	t_fixed		t;
	t_fixed		u;
}				t_hit;

#endif
