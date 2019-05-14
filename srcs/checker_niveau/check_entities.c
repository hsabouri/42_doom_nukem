/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:43:42 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/14 18:24:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

t_lvl_error	check_mat_entities(t_entity *entities, t_lvl_error error,\
size_t nentities, t_check_mat mats)
{
	// Ne plus checker les materiaux mais juste si le t_array * est dans le tableau de multisprite :D
	// A voir si on check les multi-sprite (je pense que oui)
	return (error);
}

t_list		sector_entity(t_entity *entities, size_t nentities, t_game game)
{
	t_list		error;
	t_lvl_error	*elem;
	int			cpt;

	error = lnew(NULL);
	cpt = 0;
	while (cpt < (int)nentities)
	{
		if (is_in_sector(entities[cpt].physic, game,
			entities[cpt].physic.sector_id) % 2 == 0)
		{
			elem = (t_lvl_error *)safe_malloc(sizeof(t_lvl_error), "level checker");
			elem->elem.next = NULL;
			elem->error_type = BAD_SECTOR;
			elem->entities = cpt;
			lpush(&error, (t_elem *)elem);
		}
		cpt++;
	}
	return (error);
}

u_int32_t	launch_check_entities(t_lvl_error error, t_game game,\
char *errors_text[NBR_ERROR], t_check_mat mats)
{
	error = check_mat_entities(game.entities, error, game.nentities, mats);
	if (error.error_type != NO_ERROR)
	{
		printf("%s: entities %zu\n", errors_text[error.error_type], error.entities);
		return (0);
	}
	return (1);
}
