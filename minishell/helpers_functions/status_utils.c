/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:20:08 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/13 03:26:00 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execve_handler(char *path,t_cmd *cmd, t_env *shell)
{
    execve(path, cmd->argv, shell->envp);
    perror("execve");
    free(path);
    exit(127);
}
int    setup_fds(int i,t_pipes *pipes)
{
    if (i > 0)
    {
        if (dup2(pipes->last_read,0) == -1)
        {
            perror("minishell: dup2");
            return (-1); 
        }
    }
    if (dup2(pipes->fd[1],1) == -1)
    {
        perror("minishell: dup2");
        return (-1);
    }
    if (pipes->last_read != -1)
        close(pipes->last_read);
    if (pipes->fd[1] != -1)
        close(pipes->fd[1]);
    if (pipes->fd[0] != -1)
        close(pipes->fd[0]);
    return (1);
}
