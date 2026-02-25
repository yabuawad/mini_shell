/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:34:27 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/26 14:50:05 by malhassa         ###   ########.fr       */
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
	long	num;

	num = n;
	i = intlen(num);
	ptr = (char *)malloc(intlen(num) + 1);
	if (ptr == NULL)
		return (NULL);
	if (num < 0)
	{
		ptr[0] = '-';
		num *= -1;
	}
	ptr[i--] = '\0';
	while (i > 0)
	{
		ptr[i--] = (num % 10) + '0';
		num /= 10;
	}
	if (ptr[0] != '-')
		ptr[0] = (num % 10) + '0';
	return (ptr);
}

// int	main(void)
// {
// 	printf("%s", ft_itoa(2147483647));
// }