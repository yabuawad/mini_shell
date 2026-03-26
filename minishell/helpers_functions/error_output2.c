/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 23:07:14 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/26 14:30:02 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int chdir_error(char *cmd)
{
    ft_putstr_fd("minishell: cd: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    return (1);
}
int env_error(char *cmd)
{
    ft_putstr_fd("env: '", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd("': No such file or directory\n", 2);
    return (127);         
}
void print_exit(char *message, int exit_value) 
{
    ft_putendl_fd(message, 2);
    exit(exit_value);
}
