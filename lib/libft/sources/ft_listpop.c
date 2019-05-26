/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listpop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:49:49 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:17:19 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  pop removes the last element of a list and returns of pointer onto it
*/

t_pelem		*lpremove(t_plist *list, t_pelem *del_elem)
{
	t_pelem *current;
	t_pelem *sav;

	if (!list)
		return (NULL);
	if (list->first == del_elem || list->last == del_elem)
	{
		if (list->first == del_elem)
			sav = lpshift(list);
		else
			sav = lppop(list);
	}
	else
	{
		current = del_elem;
		sav = del_elem;
		current->prev->next = current->next;
		current->next->prev = current->prev;
		current = NULL;
		list->len -= 1;
	}
	return (sav);
}

t_elem		*lpop(t_list *list)
{
	t_elem	*res;

	if (!list || !list->last)
		return (NULL);
	res = list->last;
	if (list->last == list->first)
	{
		list->len = 0;
		list->last = NULL;
		list->first = NULL;
		list->current = NULL;
		return (res);
	}
	list->last = list->first;
	while (list->last->next != res)
		list->last = list->last->next;
	list->last->next = NULL;
	list->len -= 1;
	return (res);
}

t_pelem		*lppop(t_plist *list)
{
	t_pelem	*res;

	if (!list || !list->last)
		return (NULL);
	res = list->last;
	list->last = list->last->prev;
	list->last->next = NULL;
	list->len -= 1;
	return (res);
}
