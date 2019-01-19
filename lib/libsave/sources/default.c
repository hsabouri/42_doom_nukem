/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 17:19:51 by hsabouri          #+#    #+#             */
/*   Updated: 2019/01/09 15:54:31 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <load_save.h>

t_player	player_default(void)
{
	return ((t_player) {
		(t_ph) {
			9.81,
			2,
			(t_vec3) {0, 0, 0},
			(t_vec3) {0, 0, 0},
			(t_vec3) {8, 8, 54},
			(t_vec2) {0, 0},
			0,
			0,
			0
	}});
}
