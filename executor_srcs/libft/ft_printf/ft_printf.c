/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:52:59 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/07 19:25:23 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	formatter(const char *str, int count, va_list args)
{
	if (str[count + 1] == 'c')
		return (ft_putchr(va_arg(args, int)));
	if (str[count + 1] == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (str[count + 1] == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (str[count + 1] == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (str[count + 1] == 'u')
		return (ft_unsigned(va_arg(args, unsigned int)));
	if (str[count + 1] == 'p')
		return (ft_puthexptr(va_arg(args, unsigned long)));
	if (str[count + 1] == 'x')
		return (ft_puthex(va_arg(args, unsigned long)));
	if (str[count + 1] == 'X')
		return (ft_puthexcaps(va_arg(args, unsigned int)));
	if (str[count + 1] == '%')
	{
		return (ft_putchr('%'));
		count++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			count += formatter(str, i, args);
			i += 2;
			continue ;
		}
		else
			count += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}

// int main ()
// {
// 	void * x;
// 	void *i  =  &x;

// 	ft_printf("%X\n",i);
// 	ft_printf("%p\n",x);
// 		printf("%X\n",i);
// 	printf("%p",x);
// 	// printf("cspdiuxX%");
// }