/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:51:11 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/16 16:01:25 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ldel(t_list *list)
{
	void	*next_free;
	void	*to_free;

	while ((next_free = lnext(list)))
	{
		if (to_free)
			free(to_free);
		to_free = next_free;
	}
	list->len = 0;
	list->first = NULL;
	list->current = NULL;
	list->last = NULL;
}
