/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:20:42 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/26 16:28:06 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		length;
	int		j;
	char	*ptr;

	j = 0;
	length = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(length + 1);
	if (!ptr)
		return (NULL);
	while (*s1)
	{
		ptr[j] = *s1;
		s1++;
		j++;
	}
	while (*s2)
	{
		ptr[j] = *s2;
		j++;
		s2++;
	}
	ptr[j] = '\0';
	return (ptr);
}
// int main(void)
// {
//     char *ptr = "mohamed";
//     char *str = " alhassan";
//     char *con = ft_strjoin(ptr,str);
//     printf("%s",con);
// }