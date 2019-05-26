/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:17:06 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:13:08 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*lpush(t_list *list, t_elem *elem)
{
	t_elem *current;

	if (list == NULL || elem == NULL)
		return (list);
	if (list->last)
		list->last->next = elem;
	else
		list->first = elem;
	list->len += 1;
	current = elem;
	while (current->next)
	{
		current = current->next;
		list->len += 1;
	}
	list->last = current;
	return (list);
}

t_plist		*lppush(t_plist *list, t_pelem *elem)
{
	t_pelem *current;

	if (list == NULL || elem == NULL)
		return (list);
	if (list->last != NULL)
		list->last->next = elem;
	else
		list->first = elem;
	list->len += 1;
	current = elem;
	while (current->next)
	{
		list->len += 1;
		current = current->next;
	}
	elem->prev = list->last;
	list->last = current;
	return (list);
}
