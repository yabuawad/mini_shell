/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:13:29 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/26 16:19:46 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	length;
	size_t	i;

	i = 0;
	length = ft_strlen(s);
	str = (char *)malloc(length + 1);
	if (str == NULL)
		return (NULL);
	while (i < length)
	{
		str[i] = s[i];
		i++;
	}
	str[length] = '\0';
	return (str);
}
