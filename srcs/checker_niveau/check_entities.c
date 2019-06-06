/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:43:42 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/03 11:01:33 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

static t_lvl_error	check_mat_entities(t_entity *entities, size_t nentities,
t_array *multi_mats, size_t nmulti)
{
	t_lvl_error	error;
	u_int32_t	index;
	size_t		cpt;

	cpt = 0;
	init_error(&error);
	while (cpt < nentities)
	{
		index = id_from_p(entities[cpt].mat, multi_mats, sizeof(t_array));
		if (entities[cpt].mat && index >= nmulti)
		{
			error.error_type = MATS_ENTITIES;
			error.entities = cpt;
			return (error);
		}
		cpt++;
	}
	return (error);
}

t_list				sector_entity(t_entity *entities, size_t nentities,
t_game game)
{
	t_list		error;
	t_lvl_error	*elem;
	int			cpt;

	error = lnew(NULL);
	cpt = 0;
	while (cpt < (int)nentities)
	{
		if (game.nsectors <= entities[cpt].physic.sector_id
			|| is_in_sector(entities[cpt].physic, game,
			entities[cpt].physic.sector_id) % 2 == 0)
		{
			elem = (t_lvl_error *)safe_malloc(sizeof(t_lvl_error),
				"level_checker");
			init_error(elem);
			elem->elem.next = NULL;
			elem->error_type = BAD_SECTOR;
			elem->entities = cpt;
			lpush(&error, (t_elem *)elem);
		}
		cpt++;
	}
	return (error);
}

u_int32_t			launch_check_entities(t_game game, t_env *env,
char *errors_text[NBR_ERROR])
{
	t_lvl_error error;

	error = check_mat_entities(game.entities, game.nentities, game.multi_mats,
		game.nmulti_mats);
	if (error.error_type != NO_ERROR)
	{
		ft_putstr(errors_text[error.error_type]);
		ft_putstr(": entity ");
		ft_putnbr(error.entities);
		ft_putchar('\n');
		return (check_editor(env));
	}
	return (1);
}
