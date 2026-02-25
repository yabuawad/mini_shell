/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haabu-sa <haabu-sa@amman.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:36:13 by haabu-sa          #+#    #+#             */
/*   Updated: 2025/09/07 17:35:30 by haabu-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_putchr(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_unsigned(unsigned int n);
int	ft_puthexptr(unsigned long n);
int	ft_puthex(unsigned int n);
int	ft_puthexcaps(unsigned int n);

#endif