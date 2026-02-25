/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:50:08 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/07 17:58:14 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	unlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	unfill_str(unsigned int n, char *str, int i)
{
	if (n == 0)
	{
		str[i] = '0';
		return ;
	}
	while (n > 0)
	{
		str[i--] = (n % 10) + '0';
		n = n / 10;
	}
}

int	ft_putunnbr(unsigned int n)
{
	int		i;
	char	str[12];

	i = unlen(n);
	str[i--] = '\0';
	unfill_str(n, str, i);
	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}

int	ft_unsigned(unsigned int n)
{
	return (ft_putunnbr(n));
}
