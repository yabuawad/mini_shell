/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:15:44 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/26 23:57:41 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	size_t	n;
	char	x;

	x = (unsigned char)c;
	n = ft_strlen(s);
	ptr = (char *)s;
	if (ptr[n] == x)
		return (ptr + n);
	while (n--)
	{
		if (ptr[n] == x)
			return (ptr + n);
	}
	return (NULL);
}
/*
// C program to illustrate
// the strrchr() function
#include <stdio.h>
#include <string.h>

int	main(void)
{
	// initializing string
	char str[] = "GeeksforGeeks";

	// character to be searched
	char chr = 'd';

	// Storing pointer returned by
	char *ptr = ft_strrchr(str, chr);

	// getting the position of the character
	if (ptr)
	{
		printf("Last occurrence of %c in %s is at index %ld",
				chr,
				str,
				ptr - str);
	}
	// condition for character not present
	else
	{
		printf("%c is not present in %s ", chr, str);
	}
	return (0);
}*/
