/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:49:09 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/28 17:31:59 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* fills the first n bytes of the memory area pointed to by s with the 
   constant byte c. */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*schar;

	schar = s;
	i = 0;
	while (i < n)
	{
		schar[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
