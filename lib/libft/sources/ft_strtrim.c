/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 09:28:35 by hsabouri          #+#    #+#             */
/*   Updated: 2016/11/06 16:50:55 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	len;
	size_t	slen;
	char	*dst;

	start = 0;
	slen = ft_strlen(s);
	while (ft_isblankn(s[start]) && s[start])
		start++;
	if (s[start] == '\0')
	{
		dst = ft_strnew(0);
		return (dst);
	}
	len = slen - start - 1;
	while (ft_isblankn(s[start + len]))
		len--;
	dst = ft_strsub(s, (unsigned int)start, len + 1);
	return (dst);
}
