/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:18:40 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/26 16:37:38 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	size_t	dlen;

	j = 0;
	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	i = dlen;
	if (size <= dlen)
		return (slen + size);
	while (size > (i + 1) && src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dlen + slen);
}
// int main(void)
// {

//     return(0);
// }
