/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:18:36 by hsabouri          #+#    #+#             */
/*   Updated: 2016/11/06 12:09:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;
	size_t	little_len;
	char	*ptr;

	i = 0;
	little_len = ft_strlen(little);
	ptr = (char *)big;
	if (little[0] == '\0')
		return (ptr);
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && little[j])
			j++;
		if (j == little_len)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
