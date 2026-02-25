/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 06:46:15 by mohamed           #+#    #+#             */
/*   Updated: 2026/02/25 20:28:57 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    perror_exit(char *message,int exit_code)
{
    perror(message);
    exit(exit_code);
}
int fork_error(int fd[2],t_pipes *pipes)
{
    close(fd[0]);
    close(fd[1]);
    if (pipes->last_read != -1)
        close(pipes->last_read);
    return (1);
}
int pipe_error(t_pipes *pipes)
{
    if (pipes->last_read != -1)
        close(pipes->last_read);
    return (1);
}
int path_error(t_cmd *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd->argv[0], 2);
    ft_putstr_fd(": command not found\n", 2);
    return (127);
}