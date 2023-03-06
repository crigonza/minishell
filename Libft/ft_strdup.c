/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:53:28 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/28 17:35:56 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns a pointer to a new string which is a duplicate of the string s. */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	slen;

	slen = ft_strlen(s) + 1;
	ptr = (char *)malloc(slen * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, slen);
	return (ptr);
}
