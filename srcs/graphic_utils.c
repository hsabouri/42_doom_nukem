/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 11:47:42 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/05 11:38:15 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

inline t_pix_fixed	from_pix(t_pix pixel)
{
	return ((t_pix_fixed) {f_from_int(pixel.x), f_from_int(pixel.y)});
}