/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:26:57 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/05 14:39:36 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_game		create_entity(t_vec2 pos, size_t class_id, t_game game)
{
	if ((game.entities = (t_entity *)realloc(game.entities, sizeof(t_entity)
		* (game.nentities + 1))) == NULL)
		return (game);
	game.entities[game.nentities] = game.classes[class_id];
	game.entities[game.nentities].physic.pos = vec3_new(pos.u, pos.v, 0);
	game.entities[game.nentities].spawn.pos = vec3_new(pos.u, pos.v, 0);
	game.entities[game.nentities].spawn.pos = vec3_new(pos.u, pos.v, 0);
	game.entities[game.nentities].id = game.unique_e_id;
	game.entities[game.nentities].type = game.classes[class_id].type;
	game.nentities++;
	game.unique_e_id++;
	return (game);
}
