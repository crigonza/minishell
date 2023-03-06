/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:17:50 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/28 17:38:21 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Calculates the length of the string pointed to by s, excluding the 
   terminating null byte ('\0'). */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
