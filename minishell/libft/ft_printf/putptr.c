/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:51:43 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/07 17:58:35 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_lenptr(unsigned long n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static void	fill_hexptr(unsigned long n, char *str, int i)
{
	int	nnum;

	nnum = 0;
	if (!n)
		return ;
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

int	ft_puthexptr(unsigned long n)
{
	int		i;
	char	str[20];

	if (!n)
	{
		return (write(1, "(nil)", 5));
	}
	i = hex_lenptr(n);
	str[i--] = '\0';
	fill_hexptr(n, str, i);
	i = 0;
	write(1, "0x", 2);
	while (str[i])
		write(1, &str[i++], 1);
	return (i + 2);
}
