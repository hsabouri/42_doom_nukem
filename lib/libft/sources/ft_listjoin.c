/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:20:35 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:26:40 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** join adds a list to another
*/

/*
** - if 'begin' is an empty list, 'end' is returned
** - if 'end' is an empty list, 'begin' is returned
** - if 'begin's and 'end's first element is the same, the biggest liste is
**   returned
** - if 'begin' and 'end' are valid lists, lists are joined
** - any other case have undefined behavior
** - this function is not checking for cycles
*/

t_list	*ljoin(t_list *begin, t_list *end)
{
	if (!begin)
		return (end);
	else if (!end || !end->first || (begin->first == end->first
		&& end->len <= begin->len))
		return (begin);
	else if (!begin->first || (begin->first == end->first
		&& end->len > begin->len))
		*begin = *end;
	else
	{
		begin->last->next = end->first;
		begin->last = end->last;
		begin->len += end->len;
	}
	return (begin);
}

/*
** - if 'end' is an empty list, 'begin' is returned
** - if 'begin' is an empty list, 'end' is returned
** - if 'begin's and 'end's first element is the same, the biggest liste is
**   returned
** - if 'begin' and 'end' are valid lists, lists are joined
** - any other case have undefined behavior
** - 'end.last->prev' will be overwritten
** - this function is not checking for cycles
*/

t_plist	*lpjoin(t_plist *begin, t_plist *end)
{
	if (!begin)
		return (end);
	else if (!end || !end->first || (begin->first == end->first
		&& end->len <= begin->len))
		return (begin);
	else if (!begin->first || (begin->first == end->first
		&& end->len > begin->len))
		*begin = *end;
	else
	{
		begin->last->next = end->first;
		end->first->prev = begin->last;
		begin->last = end->last;
		begin->len += end->len;
	}
	return (begin);
}
