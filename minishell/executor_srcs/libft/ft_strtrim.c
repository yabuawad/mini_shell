/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:58:24 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/27 00:04:59 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (len && ft_strchr(set, s1[len - 1]))
		len--;
	return (ft_substr(s1, i, len - i));
}
// int	main(void)
// {
// 	printf("%s", ft_strtrim("-z-----zzzz-hello-zzzz-z--z-z-z---zzz-z-z", "z-"));
// }