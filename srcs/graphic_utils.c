/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:47:42 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/19 18:23:40 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

inline t_pix_fixed	from_pix(t_pix pixel)
{
	return ((t_pix_fixed) {f_from_int(pixel.x), f_from_int(pixel.y)});
}
