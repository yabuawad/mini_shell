/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:31:58 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/19 13:36:14 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ts1;
	const unsigned char	*ts2;

	ts1 = s1;
	ts2 = s2;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*ts1 != *ts2)
			return (*ts1 - *ts2);
		ts1++;
		ts2++;
	}
	return (0);
}
