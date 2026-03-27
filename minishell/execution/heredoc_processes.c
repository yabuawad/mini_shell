/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:19:24 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/27 16:37:29 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int heredoc_input(t_redir *redir , int fd[2])
{
    char    *str;

    str = readline("> ");
    if (global_signal == SIGINT)
    {
        if (str)
            free(str);
        return (-1);
    }
    if(!str)
        return (0);
    if (ft_strcmp(str,redir->target) == 0)
    {
        if (str)
            free(str);
        return (0);
    }
    write(fd[1], str, ft_strlen(str));
    write(fd[1],"\n",1);
    free(str);
    return (1);
}
int	heredoc_fds(t_redir *redir)
{
    int		fd[2];
    int     ret;
    
    if (pipe(fd) == -1)
        return (-1);
    global_signal = 0;
    while (1)
    {
        ret = heredoc_input(redir,fd);
        if (ret <= 0)
            break;
    }
    close(fd[1]);
    if (ret == -1)
    {
        close(fd[0]);
        return (-1);
    }
    redir->fd = fd[0];
    return (1);
}

int	heredocs_with_pipes(t_cmd *cmd, t_env **shell)
{
    t_cmd	*temp;
    t_redir	*temp_redir;

    temp = cmd;
    while (temp)
    {
        temp_redir = temp->redirs;
        while (temp_redir)
        {
            if (temp_redir->type == R_HEREDOC && temp_redir->fd == -1) 
            {
                if (heredoc_fds(temp_redir) == -1)
                {
                    (*shell)->last_exit_status = 130;
                    return (-1);
                }
            }
            temp_redir = temp_redir->next_redirection;
        }
        if (!temp->has_pipe)
            break;
        temp = temp->next;
    }
    return (1);
}
int    heredoc_redirection(t_redir *redir)
{
    int fd[2];

    if (redir->fd != -1)
    {
        if (dup2(redir->fd, 0) == -1)
        {
            perror("minishell: dup2");
            close(redir->fd);
            return (0);
        }
        close(redir->fd);
        redir->fd = -1;
        return (1);
    }
    if (pipe(fd) == -1)
    {
        perror("minishell: pipe");
        return (0);
    }
    while (1)
        if (!heredoc_input(redir,fd))
            break;
    close(fd[1]);
    if (dup2(fd[0],0) == -1)
    {
        perror("minishell: dup2");
        close(fd[0]);
        return (0);
    }
    close(fd[0]);
    return (1);
}
