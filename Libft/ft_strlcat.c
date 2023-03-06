/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 11:11:14 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/30 10:09:40 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* appends the NUL-terminated string src to the end of dst. It will append at 
   most size - strlen(dst) - 1 bytes, NUL-terminating the result. */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	tlen;
	size_t	j;
	size_t	i;

	i = 0;
	j = ft_strlen(dst);
	tlen = ft_strlen(src);
	if (dstsize == 0)
		return (tlen);
	else if (dstsize < ft_strlen(dst))
		tlen = tlen + dstsize;
	else
		tlen = tlen + ft_strlen(dst);
	while (j < (dstsize - 1) && src[i] != '\0')
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (tlen);
}
