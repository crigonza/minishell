/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:51:01 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/28 17:39:59 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Compares the the first n bytes of two strings s1 and s2                    */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*pts1;
	unsigned char	*pts2;

	pts1 = (unsigned char *)s1;
	pts2 = (unsigned char *)s2;
	while (n--)
	{
		if (*pts1 != *pts2)
			return (*pts1 - *pts2);
		else if (*pts1 == '\0' || *pts2 == '\0')
			return (0);
		pts1++;
		pts2++;
	}
	return (0);
}
