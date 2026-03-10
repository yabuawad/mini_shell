/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 06:46:15 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/11 01:18:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    perror_exit(char *message,int exit_code)
{
    perror(message);
    exit(exit_code);
}
int pipes_cleanup(t_pipes *pipes, int i)
{
    int j;

    j = 0;
    if (pipes->fd[0] != -1)
        close(pipes->fd[0]);
    if (pipes->fd[1] != -1)
        close(pipes->fd[1]);
    if (pipes->last_read != -1)
        close(pipes->last_read);
    while (j < i)
    {
        waitpid(pipes->pids[j],NULL,0);
        j++;
    }
    if (pipes->pids)
        free(pipes->pids);
    return (1);
}
int export_error(char *cmd)
{
    ft_putstr_fd("minishell: export: ",2);
    ft_putstr_fd(cmd,2);
    ft_putendl_fd(": not a valid identifier",2);
    return (1);
}
int path_error(t_cmd *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd->argv[0], 2);
    ft_putstr_fd(": command not found\n", 2);
    return (127);
}
int exec_error(char *cmd)
{
    struct stat st;

    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    if (stat(cmd, &st) == -1)
    {
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        return (127);
    }
    if (S_ISDIR(st.st_mode))
    {
        ft_putstr_fd("Is a directory\n", 2);
        return (126);
    }
    ft_putstr_fd("Permission denied\n", 2);
    return (126);
}
int chdir_error(char *cmd)
{
    ft_putstr_fd("minishell: cd: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    return (1);
}
