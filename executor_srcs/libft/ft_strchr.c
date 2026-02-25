/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:39:06 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/23 16:27:53 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	x;

	x = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == x)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == x)
		return ((char *)s + i);
	return (NULL);
}
// int main()
// {
//     // define a string
//     const char* str = "GeeksforGdeks";
//     // define a char ch to be searched in str
//     char ch = 'd';

//     // Use strchr to find the first occurrence of the
//     // character 's'
//     const char* result = ft_strchr(str, ch);

//    printf("%s",result);

//     return (0);
// }