/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:34:26 by crigonza          #+#    #+#             */
/*   Updated: 2022/05/03 18:10:48 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Copies  n  bytes  from memory area src to memory area dest                 */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const char			*schar;
	unsigned char		*dchar;

	schar = (const char *)src;
	dchar = (unsigned char *)dest;
	i = 0;
	if (n == 0 || dest == src)
		return (dest);
	while (i < n)
	{
		dchar[i] = schar[i];
		i++;
	}
	return (dest);
}
