/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:25:14 by hsabouri          #+#    #+#             */
/*   Updated: 2016/11/30 10:49:32 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memjoin(const void *s1, const void *s2, size_t len1, size_t len2)
{
	char	*str;

	if (len1 + len2 > 0)
	{
		str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (len1 > 0)
			ft_memcpy(str, s1, len1);
		if (len2 > 0)
			ft_memcpy(str + len1, s2, len2);
		str[len1 + len2] = '\0';
	}
	else
		return (NULL);
	return (str);
}
