/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:10:52 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/28 17:30:33 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Copies n bytes from memory area src to memory area dest. */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*sp;
	unsigned char	*dp;

	sp = (unsigned char *)src;
	dp = (unsigned char *)dest;
	i = 0;
	if (n == 0 || src == dest)
		return (dest);
	if (dp > sp)
	{
		while (n--)
			dp[n] = sp[n];
		return (dest);
	}
	while (i < n)
	{
		dp[i] = sp[i];
		i++;
	}
	return (dest);
}
