/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:23:34 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/28 17:41:28 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Returns a pointer to the last occurrence of the character c in the string s */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*lastf;

	i = 0;
	lastf = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			lastf = (char *)&s[i];
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (lastf);
}
