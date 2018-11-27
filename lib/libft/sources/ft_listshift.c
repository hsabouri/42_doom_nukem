/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listshift.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                            j                    +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:52:29 by hugo              #+#    #+#             */
/*   Updated: 2018/11/09 14:56:44 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  shift removes the first element of the list
*/

t_elem  *lshift(t_list *list)
{
    t_elem *res;

    if (list->first == NULL)
        return (NULL);
    res = list->first;
    if (list->first == list->last)
    {
        list->first = NULL;
        list->last = NULL;
        list->len = 0;
        return (res);
    }
    list->first = list->first->next;
    res->next = NULL;
    list->len -= 1;
    return (res);
}

t_pelem  *lpshift(t_plist *list)
{
    t_pelem *res;

    if (list->first == NULL)
        return (NULL);
    res = list->first;
    if (list->first == list->last)
    {
        list->first = NULL;
        list->last = NULL;
        list->len = 0;
        return (res);
    }
    list->first = list->first->next;
    list->first->prev = NULL;
    res->next = NULL;
    res->prev = NULL;
    list->len -= 1;
    return (res);
}