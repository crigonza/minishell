/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:34:43 by crigonza          #+#    #+#             */
/*   Updated: 2022/05/05 17:29:30 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates memory for an array of nmemb elements of size bytes each and 
   returns a pointer to the allocated memory.*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if (nmemb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
