/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:02:16 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/27 16:00:31 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;

	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (cdest > csrc)
	{
		while (n--)
			*(cdest + n) = *(csrc + n);
	}
	else
	{
		while (n--)
			*(cdest)++ = *(csrc)++;
	}
	return (dest);
}
// int	main(void)
// {
// 	// char	str[100] = "Learningisfun";
// 	// printf("Original string :%s\n ", str);
// 	printf("%s",ft_memmove(((void*)0), ((void*)0), 0));
// 	// printf("memmove overlap : %s\n ", str);
// }
