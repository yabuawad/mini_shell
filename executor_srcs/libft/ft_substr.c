/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:37 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/27 00:09:36 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	char	*temp;
	size_t	j;

	j = 0;
	temp = (char *)s + start;
	if (ft_strlen(s) <= start)
	{
		substring = (char *)malloc(1);
		if (substring == NULL)
			return (NULL);
		substring[0] = '\0';
		return (substring);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substring = (char *)malloc(len + 1);
	if (substring == NULL)
		return (NULL);
	while (len--)
		substring[j++] = *temp++;
	substring[j] = '\0';
	return (substring);
}

// int main(void)
// {
// 	char *str;
// 	char *result;
//    str = strdup("0123456789");
// 	result = ft_substr(str, 9, 10);
//     printf("%s",result);
// }