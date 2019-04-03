/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:07:51 by hsabouri          #+#    #+#             */
/*   Updated: 2019/04/01 18:23:20 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	clean_childs(t_array childs)
{
	t_component *current;

	while ((current = (t_component *)apop(&childs)))
		destroy_component(current);
	if (childs.mem)
		free(childs.mem);
}