/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:48:40 by hsabouri          #+#    #+#             */
/*   Updated: 2016/11/09 19:36:16 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long	nb;
	int		power;

	nb = 0;
	power = 1;
	while (ft_isspace(*str))
		str++;
	if (*(str) == '-')
	{
		power = -1;
		str++;
	}
	else if (*(str) == '+')
		str++;
	while (*str <= '9' && *str >= '0')
	{
		nb += (*str - '0') * power;
		nb *= 10;
		str++;
	}
	return ((int)(nb / 10));
}
