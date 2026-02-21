/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:08:23 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/27 15:58:58 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;
	size_t				i;

	i = 0;
	cdest = (unsigned char *)dest;
	csrc = (const unsigned char *)src;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}

// int	main(void)
// {
// // 	char	str1[];
// // 	char	str2[6];
// // 	char	s[20];

// // 	str1[] = "Geeks";
// // 	str2[6] = "";
// // 	s[20] = "            ";
// 	// Copies contents of str2 to str1
// 	printf("%s", (char *)ft_memcpy(((void *)0), ((void *)0), 0));
// 	// printf("%s", (char *)memcpy(((void*)0), ((void*)0), 3));
// 	// printf("str2 after memcpy:");
// 	// printf("%s\n",str2);
// 	return (0);
// }
