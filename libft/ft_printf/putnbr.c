/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:49:20 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/07 17:57:37 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	fill_str(int n, char *str, int i)
{
	while (n > 0)
	{
		str[i--] = (n % 10) + '0';
		n = n / 10;
	}
}

int	ft_putnbr(int n)
{
	int		i;
	char	str[12];

	if (n == 0)
	{
		return (write(1, "0", 1));
	}
	if (n == -2147483648)
	{
		return (write(1, "-2147483648", 11));
	}
	i = len(n);
	str[i--] = '\0';
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	fill_str(n, str, i);
	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}
