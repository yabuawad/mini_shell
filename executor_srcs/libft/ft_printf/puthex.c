/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:00:07 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/07 18:01:58 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_len(unsigned int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static void	fill_hex(unsigned int n, char *str, int i)
{
	int	nnum;

	nnum = 0;
	while (n > 0)
	{
		nnum = (n % 16);
		if (nnum <= 9 && nnum >= 0)
			str[i--] = nnum + '0';
		else
			str[i--] = 'a' + (nnum - 10);
		n = n / 16;
	}
}

int	ft_puthex(unsigned int n)
{
	int		i;
	char	str[16];

	if (n == 0)
	{
		return (write(1, "0", 1));
	}
	i = hex_len(n);
	str[i--] = '\0';
	fill_hex(n, str, i);
	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}

static void	fill_hexcaps(unsigned int n, char *str, int i)
{
	int	nnum;

	nnum = 0;
	while (n > 0)
	{
		nnum = (n % 16);
		if (nnum <= 9 && nnum >= 0)
			str[i--] = nnum + '0';
		else
			str[i--] = 'A' + (nnum - 10);
		n = n / 16;
	}
}

int	ft_puthexcaps(unsigned int n)
{
	int		i;
	char	str[16];

	if (n == 0)
	{
		return (write(1, "0", 1));
	}
	i = hex_len(n);
	str[i--] = '\0';
	fill_hexcaps(n, str, i);
	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}
