/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:25:45 by hsabouri          #+#    #+#             */
/*   Updated: 2016/11/10 13:15:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countsplit(char const *s, char c)
{
	size_t	str_len;
	size_t	i;
	size_t	len;

	len = 0;
	str_len = ft_strlen(s);
	i = 0;
	while (i < str_len)
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
			i++;
		if (s[i - 1] != c && s[i - 1])
			len++;
	}
	return (len);
}

static char		**ft_strtotab(char **tab, char const *s, char c, size_t len)
{
	size_t	cur_start;
	size_t	cur_len;
	size_t	i;

	i = 0;
	cur_start = 0;
	while (i < len)
	{
		cur_start += cur_len;
		cur_len = 0;
		while (s[cur_start] == c && s[cur_start])
			cur_start++;
		while (s[cur_start + cur_len] != c && s[cur_start + cur_len])
			cur_len++;
		tab[i] = ft_strsub(s, (unsigned int)cur_start, cur_len);
		i++;
	}
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	len;

	len = 0;
	if (*s)
		len = ft_countsplit(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	tab = ft_strtotab(tab, s, c, len);
	tab[len] = NULL;
	return (tab);
}
