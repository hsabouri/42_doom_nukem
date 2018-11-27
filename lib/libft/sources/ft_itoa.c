/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:07:29 by hsabouri          #+#    #+#             */
/*   Updated: 2016/11/08 14:43:23 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itomem(int n, size_t *size)
{
	char	*str;

	*size = (n < 0) ? 2 : 1;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		(*size)++;
	}
	if (!(str = ft_strnew(*size)))
		return (NULL);
	return (str);
}

char		*ft_itoa(int n)
{
	char	*nbr;
	size_t	size;
	long	nb;

	if (n == -2147483648)
	{
		if (!(nbr = ft_strcpy(ft_strnew(
		ft_strlen("-2147483648")), "-2147483648")))
			return (NULL);
		else
			return (nbr);
	}
	if (!(nbr = ft_itomem(n, &size)))
		return (NULL);
	nb = (n < 0) ? -n : n;
	if (n < 0)
		nbr[0] = '-';
	while (size > ((n < 0) ? 1 : 0))
	{
		nbr[size - 1] = nb % 10 + '0';
		nb /= 10;
		size--;
	}
	return (nbr);
}
