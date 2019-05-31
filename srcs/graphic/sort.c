/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:12:42 by hsabouri          #+#    #+#             */
/*   Updated: 2019/05/30 16:32:30 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic.h>
#include "./sort.h"

void			swap_entities(t_section_entity *a, t_section_entity *b)
{
	t_section_entity tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_render		sort_entities(t_render render)
{
	int			current_id;
	int			s_id;
	int			swap_id;
	t_fixed		s_dis;
	t_fixed		current_dis;

	current_id = 0;
	while (current_id < render.nentities)
	{
		current_dis = render.entities[current_id].entity.dis;
		s_id = current_id + 1;
		swap_id = -1;
		while (s_id < render.nentities)
		{
			s_dis = render.entities[s_id].entity.dis;
			if (s_dis <= current_dis)
				swap_id = s_id;
			++s_id;
		}
		if (swap_id >= 0)
			swap_entities(&render.entities[current_id],
			&render.entities[swap_id]);
		++current_id;
	}
	return (render);
}
