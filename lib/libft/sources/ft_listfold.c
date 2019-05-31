/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listfold.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:34:31 by hugo              #+#    #+#             */
/*   Updated: 2019/05/24 14:31:56 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  fold will call a function on each element of a list, passing a pointer to
**  a value batween calls
**  Be careful of memory leaks, '*acc' must be allocated or on the stack
*/

void	*lfold(const t_list *list, void *acc, void *(*f)(const t_elem *,
void *))
{
	t_elem	*current;

	if (!list)
		return (NULL);
	current = list->first;
	if (current == NULL)
		return (NULL);
	acc = (*f)(current, acc);
	while (current->next)
	{
		current = current->next;
		acc = (*f)(current, acc);
	}
	return (acc);
}

void	*lfoldi(const t_list *list, void *acc, void *(*f)(const t_elem *,
void *,
size_t))
{
	t_elem	*current;
	size_t	i;

	if (!list)
		return (NULL);
	current = list->first;
	if (current == NULL)
		return (NULL);
	i = 0;
	acc = (*f)(current, acc, i);
	while (current->next)
	{
		current = current->next;
		i++;
		acc = (*f)(current, acc, i);
	}
	return (acc);
}

void	*lpfold(const t_plist *list, void *acc, void *(*f)(const t_pelem *,
void *))
{
	t_pelem	*current;

	if (!list)
		return (NULL);
	current = list->first;
	if (current == NULL)
		return (NULL);
	acc = (*f)(current, acc);
	while (current->next)
	{
		current = current->next;
		acc = (*f)(current, acc);
	}
	return (acc);
}

void	*lpfoldi(const t_plist *list, void *acc, void *(*f)(const t_pelem *,
void *,
size_t))
{
	t_pelem	*current;
	size_t	i;

	if (!list)
		return (NULL);
	current = list->first;
	if (current == NULL)
		return (NULL);
	i = 0;
	acc = (*f)(current, acc, i);
	while (current->next)
	{
		current = current->next;
		i++;
		acc = (*f)(current, acc, i);
	}
	return (acc);
}
