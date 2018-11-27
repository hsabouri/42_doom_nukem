/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:17:06 by hugo              #+#    #+#             */
/*   Updated: 2018/11/13 14:34:19 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** push adds an element to a list, the element can be a list
*/

/*
** - '*elem' must be allocated
**   or be accessible where you use lists' functions.
** - 'elem->next' will be followed and added at the list
*/

t_list  *lpush(t_list *list, t_elem *elem)
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

/*
** - '*elem' must be allocated
**   or be accessible where you use lists' functions.
** - 'elem->next' will be followed and pushed at the list
** - 'elem->prev' will be overwritten
*/

t_plist  *lppush(t_plist *list, t_pelem *elem)
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