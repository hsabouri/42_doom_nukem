/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listforeach.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:15:29 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:33:58 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  foreach applies a function on each element of the list
**  foreachi applies a function on each element of the list while keeping track
**  of the index
*/

t_list	*lforeach(t_list *list, void (*f)(t_elem *elem))
{
	t_elem	*current;

	if (!list)
		return (NULL);
	current = list->first;
	if (current == NULL)
		return (list);
	(*f)(current);
	while (current->next)
	{
		current = current->next;
		(*f)(current);
	}
	return (list);
}

t_list	*lforeachi(t_list *list, void (*f)(t_elem *elem, size_t i))
{
	t_elem	*current;
	size_t	i;

	if (!list)
		return (NULL);
	current = list->first;
	if (current == NULL)
		return (list);
	i = 0;
	(*f)(current, i);
	while (current->next)
	{
		i++;
		current = current->next;
		(*f)(current, i);
	}
	return (list);
}

t_plist	*lpforeach(t_plist *plist, void (*f)(t_pelem *pelem))
{
	t_pelem	*current;

	if (!plist)
		return (NULL);
	current = plist->first;
	if (current == NULL)
		return (plist);
	(*f)(current);
	while (current->next)
	{
		current = current->next;
		(*f)(current);
	}
	return (plist);
}

t_plist	*lpforeachi(t_plist *plist, void (*f)(t_pelem *pelem, size_t i))
{
	t_pelem	*current;
	size_t	i;

	if (!plist)
		return (NULL);
	current = plist->first;
	if (current == NULL)
		return (plist);
	i = 0;
	(*f)(current, i);
	while (current->next)
	{
		i++;
		current = current->next;
		(*f)(current, i);
	}
	return (plist);
}
