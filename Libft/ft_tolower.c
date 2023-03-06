/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:21:09 by crigonza          #+#    #+#             */
/*   Updated: 2022/04/23 07:24:27 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Convert uppercase letters to lowercase.                                    */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
