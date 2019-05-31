/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:52:52 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:24:40 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** - '*elem' returned by '*f' must be allocated
** - 'elem->next' will be followed and added to the list
** - if '*f' returns null, no element will be added to the list
**   allowing you to filter the list
*/

t_list	lmap(const t_list *list, t_elem *(*f)(const t_elem *))
{
	t_list	new_list;
	t_elem	*current;

	if (!list)
		return (lnew(NULL));
	current = list->first;
	if (current == NULL)
		return (*list);
	new_list = lnew((*f)(current));
	while (current->next)
	{
		current = current->next;
		new_list.push(&new_list, (*f)(current));
	}
	return (new_list);
}

t_list	lmapi(const t_list *list, t_elem *(*f)(const t_elem *, size_t i))
{
	t_list	new_list;
	t_elem	*current;
	size_t	i;

	if (!list)
		return (lnew(NULL));
	current = list->first;
	if (current == NULL)
		return (*list);
	i = 0;
	new_list = lnew((*f)(current, i));
	while (current->next)
	{
		i++;
		current = current->next;
		new_list.push(&new_list, (*f)(current, i));
	}
	return (new_list);
}

/*
** - '*elem' returned by '*f' must be allocated
** - 'elem->next' will be followed and added to the list
** - returned 'elem->prev' will be overwritten
** - if '*f' returns null, no element will be added to the list
**   allowing you to filter the list
*/

t_plist	lpmap(const t_plist *list, t_pelem *(*f)(const t_pelem *))
{
	t_plist	new_list;
	t_pelem	*current;

	if (!list)
		return (lpnew(NULL));
	current = list->first;
	if (current == NULL)
		return (*list);
	new_list = lpnew((*f)(current));
	while (current->next)
	{
		current = current->next;
		new_list.push(&new_list, (*f)(current));
	}
	return (new_list);
}

t_plist	lpmapi(const t_plist *plist, t_pelem *(*f)(const t_pelem *, size_t i))
{
	t_plist	new_list;
	t_pelem	*current;
	size_t	i;

	if (!plist)
		return (lpnew(NULL));
	current = plist->first;
	if (current == NULL)
		return (*plist);
	i = 0;
	new_list = lpnew((*f)(current, i));
	while (current->next)
	{
		i++;
		current = current->next;
		new_list.push(&new_list, (*f)(current, i));
	}
	return (new_list);
}
