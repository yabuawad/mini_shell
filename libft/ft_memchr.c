/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:26:00 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/27 13:51:26 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	x;

	x = (unsigned char)c;
	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == x)
			return ((void *)str);
		str++;
	}
	return (0);
}
