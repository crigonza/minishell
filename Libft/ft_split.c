/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:22:55 by crigonza          #+#    #+#             */
/*   Updated: 2022/05/05 17:21:53 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wcounter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] != c)
	{
		i++;
		count++;
	}
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

char	**ft_freestr(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		str[i] = NULL;
		i--;
	}
	free(str);
	str = NULL;
	return (NULL);
}

char	**ft_addsubstr(char **str, char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (s[j] && s[j] != c)
				j++;
			str[i] = ft_substr(s, 0, j);
			if (!str[i])
				return (ft_freestr(str, i));
			i++;
			s = s + j;
		}
		else
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**splitstr;

	if (!s)
		return (NULL);
	splitstr = (char **)malloc(sizeof(char *) * (ft_wcounter(s, c) + 1));
	if (!splitstr)
		return (NULL);
	splitstr = ft_addsubstr(splitstr, s, c);
	return (splitstr);
}
