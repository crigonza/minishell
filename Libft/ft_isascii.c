/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:37:59 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/28 17:23:29 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks whether c is a 7-bit unsigned char value that fits into the ASCII  
	character set. */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
