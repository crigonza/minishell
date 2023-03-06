/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 10:35:14 by crigonza          #+#    #+#             */
/*   Updated: 2022/05/03 19:46:40 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sstr;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen > len)
		slen = len;
	sstr = (char *)malloc(slen * sizeof(char) + 1);
	if (!sstr)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		sstr[i] = s[start];
		start++;
		i++;
	}
	sstr[i] = '\0';
	return (sstr);
}
