/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:12:21 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/28 17:28:21 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Compares the first n bytes of the memory areas s1 and s2. */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	while (n--)
	{
		if (*ptrs1 != *ptrs2)
			return (*ptrs1 - *ptrs2);
		ptrs1++;
		ptrs2++;
	}
	return (0);
}
