/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:09:53 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/28 17:18:46 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Erases the data in the n bytes of the memory starting at the 
   location pointed to by s. */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
