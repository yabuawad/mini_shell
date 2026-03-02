/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 06:46:15 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/02 18:02:33 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    perror_exit(char *message,int exit_code)
{
    perror(message);
    exit(exit_code);
}
int pipes_cleanup(t_pipes *pipes)
{
    if (pipes->fd[0] != -1) //  or if (pipes->fd[0] == -1)?
        close(pipes->fd[0]);
    if (pipes->fd[1] != -1)// same for here?
        close(pipes->fd[1]);
    if (pipes->last_read != -1)
        close(pipes->last_read);
    if (pipes->pids)
        free(pipes->pids);
    return (1);
}
int export_error(char *cmd)
{
    ft_putstr_fd("minishell: export: ",2);
    ft_putstr_fd(cmd,2);
    ft_putendl_fd(" : not a valid identifier",2);
    return (1);
}
int path_error(t_cmd *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd->argv[0], 2);
    ft_putstr_fd(": command not found\n", 2);
    return (127);
}
int chdir_error(char *cmd)
{
    ft_putstr_fd("minishell: cd: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": No such file or directory\n", 2);
    return (1);
}
