/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:06:57 by hugo              #+#    #+#             */
/*   Updated: 2019/05/30 16:44:31 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <graphic.h>

t_color	color_filter(t_color a, t_color filter);
t_color	color_superpose(t_color a, t_color b);

#endif
