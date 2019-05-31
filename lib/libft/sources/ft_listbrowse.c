/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listbrowse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:26:34 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:29:06 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  next will return one element at each call, from beginning to end
**  then return NULL, then begin again
**  previous is in the other way
*/

t_elem	*lnext(t_list *list)
{
	if (list->current)
	{
		list->current = list->current->next;
		return (list->current);
	}
	else
	{
		list->current = list->first;
		return (list->current);
	}
}

t_pelem	*lpnext(t_plist *list)
{
	return (t_pelem *)lnext((t_list *)list);
}

t_pelem	*lprevious(t_plist *list)
{
	if (list->current)
	{
		list->current = list->current->prev;
		return (list->current);
	}
	else
	{
		list->current = list->last;
		return (list->current);
	}
}
