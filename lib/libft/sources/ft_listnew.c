/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:47:10 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:22:08 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  new creates a new list starting with 'elem'
*/

/*
** - '*first' must be allocated
**   or be accessible where you use lists' functions
**   or NULL
** - '*first->next' must be initialized and valid
*/

static t_list	lassign(t_list list)
{
	list.push = &lpush;
	list.insert = &linsert;
	list.map = &lmap;
	list.mapi = &lmapi;
	list.foreach = &lforeach;
	list.foreachi = &lforeachi;
	list.join = &ljoin;
	list.fold = &lfold;
	list.foldi = &lfoldi;
	list.pop = &lpop;
	list.shift = &lshift;
	list.next = &lnext;
	return (list);
}

t_list			lnew(t_elem *first)
{
	t_list	res;
	t_elem	*current;

	res.first = first;
	current = first;
	if (first == NULL)
		res.len = 0;
	else
	{
		res.len = 1;
		while (current->next)
		{
			current = current->next;
			res.len++;
		}
	}
	res.current = NULL;
	res.last = current;
	return (lassign(res));
}

/*
** - '*first' must be allocated
**  or be accessible where you use lists' functions
**  or NULL
** - 'first->next' must be initialized and valid
** - 'first->prev' is untouched, list begins at 'first' even
**  if 'first->prev' exists allowing you to create sublists
*/

static t_plist	lpassign(t_plist list)
{
	list.push = &lppush;
	list.insert = &lpinsert;
	list.map = &lpmap;
	list.mapi = &lpmapi;
	list.foreach = &lpforeach;
	list.foreachi = &lpforeachi;
	list.join = &lpjoin;
	list.fold = &lpfold;
	list.foldi = &lpfoldi;
	list.pop = &lppop;
	list.shift = &lpshift;
	list.next = &lpnext;
	list.previous = &lprevious;
	return (list);
}

t_plist			lpnew(t_pelem *first)
{
	t_plist	res;
	t_pelem	*current;
	t_pelem	*last;

	res.first = first;
	current = first;
	if (first == NULL)
		res.len = 0;
	else
	{
		res.len = 1;
		while (current->next)
		{
			last = current;
			current = current->next;
			current->prev = last;
			res.len++;
		}
	}
	res.current = NULL;
	res.last = current;
	return (lpassign(res));
}
