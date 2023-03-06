/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:51:49 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/30 13:17:07 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nblen(int n)
{
	int			i;
	long		nb;

	i = 0;
	nb = n;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		i = 1;
	}
	while (nb)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			nlen;
	char		*str;
	long		nb;

	nlen = ft_nblen(n);
	nb = n;
	str = (char *)malloc(sizeof(char) * (nlen + 1));
	if (!str)
		return (NULL);
	str[nlen--] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	while (nb)
	{
		str[nlen] = (nb % 10) + 48;
		nb = nb / 10;
		nlen--;
	}
	return (str);
}
