/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:34:27 by malhassa          #+#    #+#             */
/*   Updated: 2026/04/04 19:04:20 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int x)
{
	int	i;

	i = 0;
	if (x == 0)
		return (1);
	if (x == -2147483648)
		return (11);
	if (x < 0)
	{
		x *= -1;
		i++;
	}
	while (x > 0)
	{
		x = x / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	int		min_i;
	long	num;

	num = n;
	i = intlen(n);
	ptr = (char *)malloc(i + 1);
	if (ptr == NULL)
		return (NULL);
	min_i = 0;
	if (num < 0)
	{
		ptr[0] = '-';
		num *= -1;
		min_i = 1;
	}
	ptr[i--] = '\0';
	while (i >= min_i)
	{
		ptr[i--] = (num % 10) + '0';
		num /= 10;
	}
	return (ptr);
}
