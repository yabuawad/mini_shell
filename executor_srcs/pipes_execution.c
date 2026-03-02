/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:52:58 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/02 03:34:17 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int    wait_for_all(t_pipes *pipes)
{
    int status;
    int i;

    i = 0;
    while(i < pipes->cmds_length)
    {
        waitpid(pipes->pids[i],&status,0);
        i++;
    }
    return (WEXITSTATUS(status));
}
static int last_process(t_cmd *cmd,t_env *pipeline, t_pipes *pipes, int i)
{
    int status;
    
    if (!cmd)
        return (pipes_cleanup(pipes));
    pipes->pids[i] = fork();
    if (pipes->pids[i] < 0)
        return (pipes_cleanup(pipes));
    if (pipes->pids[i] == 0)
    {
        if (pipes->last_read != -1)
            dup2(pipes->last_read,0);
        if (pipes->last_read != -1)
            close(pipes->last_read);
        if (cmd->redirs)
            exit(check_redirection(cmd,pipeline));
        else if (is_builtin(cmd->argv[0]))
            exit(execute_builtin(cmd, pipeline));
        else
            exit(execute_command(cmd, pipeline));
    }
    if (pipes->last_read != -1)
        close(pipes->last_read);
    status = wait_for_all(pipes);
    pipes_cleanup(pipes);
    return (status);
}

static void child_process(t_pipes *pipes,int i ,t_cmd *cmd, t_env *pipeline)
{
    if (i > 0)
        dup2(pipes->last_read,0); // 
    dup2(pipes->fd[1],1); // dup2 protection?
    if (pipes->last_read != -1)
        close(pipes->last_read);
    close(pipes->fd[1]);   // close protection?
    close(pipes->fd[0]);
    if (cmd->redirs)
        exit(check_redirection(cmd,pipeline));
    else if (is_builtin(cmd->argv[0]))
        exit(execute_builtin(cmd, pipeline));
    else if (!cmd || !cmd->argv || !cmd->argv[0])
        exit(0);
    else
        exit(execute_command(cmd, pipeline)); // double fork?
}
static int    before_execution(t_cmd *cmd,t_pipes *pipes)
{
    int i;
    t_cmd   *temp;
    
    temp = cmd;
    i = 1;
    while(temp && temp->has_pipe == 1)
    {
        i++;
        temp = temp->next;
    }
    pipes->cmds_length = i;
    pipes->pids = malloc(sizeof(pid_t) * pipes->cmds_length);
    if (!pipes->pids)
        return (0);
    pipes->last_read = -1; // maybe also fd[0]&fd[1] as -1, i need it for close protection
    return (1);
}
int apply_pipe(t_cmd *cmd,t_env *pipeline)
{
    t_pipes pipes;
    int status;
    int i;
    
    if (!before_execution(cmd,&pipes))
        return (1); // should i display an error messgae here?
    i = 0;
    while (cmd && cmd->has_pipe)
    {
        if (pipe(pipes.fd) == -1)
            return (pipes_cleanup(&pipes));
        pipes.pids[i] = fork();
        if (pipes.pids[i] < 0)
            return (pipes_cleanup(&pipes));
        if (pipes.pids[i] == 0)
            child_process(&pipes,i,cmd,pipeline);
        close(pipes.fd[1]);
        if (pipes.last_read != -1)
            close(pipes.last_read);
        pipes.last_read = pipes.fd[0];
        cmd = cmd->next;
        i++;
    }
    status = last_process(cmd,pipeline,&pipes,i);
    return (status);
}
