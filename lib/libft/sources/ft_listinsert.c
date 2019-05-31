/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listinsert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:27:43 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:28:18 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** insert adds an element at the beginning of the list
*/

/*
** - '*elem' must be allocated
**   or be accessible where you use lists' functions.
** - 'elem->next' will be overwritten
*/

t_list	*linsert(t_list *list, t_elem *elem)
{
	t_elem *current;

	if (list == NULL || elem == NULL)
		return (list);
	list->len += 1;
	current = elem;
	while (current->next)
	{
		current = current->next;
		list->len += 1;
	}
	current->next = list->first;
	list->first = elem;
	if (list->last == NULL)
		list->last = current;
	return (list);
}

/*
** - '*elem' must be allocated
**   or be accessible where you use lists' functions.
** - 'elem->next' will be overwritten
*/

t_plist	*lpinsert(t_plist *list, t_pelem *elem)
{
	t_pelem *current;

	if (list == NULL || elem == NULL)
		return (list);
	list->len += 1;
	current = elem;
	while (current->next)
	{
		current = current->next;
		list->len += 1;
	}
	current->next = list->first;
	if (list->first)
		list->first->prev = current;
	list->first = elem;
	if (list->last == NULL)
		list->last = current;
	return (list);
}
