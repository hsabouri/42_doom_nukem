/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listpop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:49:49 by hugo              #+#    #+#             */
/*   Updated: 2018/11/12 11:05:27 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  pop removes the last element of a list and returns of pointer onto it
*/

t_elem  *lpop(t_list *list)
{
    t_elem  *res;

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
    return (res);
}

t_pelem *lppop(t_plist *list)
{
    t_pelem  *res;

    if (!list || !list->last)
        return (NULL);
    res = list->last;
    list->last = list->last->prev;
    list->last->next = NULL;
    return (res);
}