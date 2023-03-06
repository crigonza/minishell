/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:22:38 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/28 17:30:19 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Scans the initial n bytes of the memory pointed to by s for the first     
   instance of c. */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*schar;

	schar = (unsigned char *)s;
	while (n--)
	{
		if (*schar == (unsigned char)c)
			return ((void *)schar);
		schar++;
	}
	return (NULL);
}
