/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:21:22 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/12 16:32:17 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../common/translate_id.h"
#include <doom.h>
#include <editor.h>

t_player	take_damage(t_player player, t_entity entity, float span)
{
	static float	last = 5.0;

	last -= (span * entity.data) / 10;
	if (last <= 0.0)
	{
		player.my_entity.life -= 5;
		last = 5.0;
	}
	return (player);
}
