/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:36:19 by yabuawad          #+#    #+#             */
/*   Updated: 2026/04/05 11:36:21 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chdir_error(char *cmd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	env_error(char *cmd)
{
	ft_putstr_fd("env: '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (127);
}

void	print_exit(char *message, int exit_value)
{
	ft_putendl_fd(message, 2);
	exit(exit_value);
}

int	dup2_error(int fd)
{
	perror("minishell: dup2");
	close(fd);
	return (0);
}
